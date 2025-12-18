# Structures miniRT

## Types de base (`vec3.h`)

| Type | Description |
|------|-------------|
| `t_vec3` | Vecteur 3D (tableau de 3 `double`) |
| `t_point3` | Alias de `t_vec3` pour les positions |
| `t_color3` | Alias de `t_vec3` pour les couleurs RGB |

---

## Structures de scène (`minirt.h`)

### Éléments uniques (obligatoires)

#### `t_ambient` - Lumière ambiante
```
Format .rt: A 0.2 255,255,255
```
| Champ | Type | Description |
|-------|------|-------------|
| `ratio` | `double` | Intensité [0.0, 1.0] |
| `color` | `t_color3` | Couleur RGB [0-255] |
| `is_set` | `int` | Flag (doit être défini une seule fois) |

#### `t_camera` - Caméra
```
Format .rt: C -50,0,20 0,0,1 70
```
| Champ | Type | Description |
|-------|------|-------------|
| `pos` | `t_point3` | Position de la caméra |
| `dir` | `t_vec3` | Direction normalisée [-1,1] |
| `fov` | `double` | Champ de vision [0-180] |
| `is_set` | `int` | Flag (doit être défini une seule fois) |
| `image_dimension[2]` | `unsigned int` | Largeur/Hauteur image |
| `viewport_dimension[2]` | `t_vec3` | Dimensions viewport |
| `pixel_length[2]` | `t_vec3` | Taille d'un pixel |
| `first_pixel_location` | `t_point3` | Position du premier pixel |
| `aspect_ratio` | `float` | Ratio largeur/hauteur |

---

### Éléments multiples

#### `t_light` - Source lumineuse
```
Format .rt: L -40,50,0 0.6 255,255,255
```
| Champ | Type | Description |
|-------|------|-------------|
| `pos` | `t_point3` | Position |
| `brightness` | `double` | Intensité [0.0, 1.0] |
| `color` | `t_color3` | Couleur (bonus, défaut blanc) |

---

### Objets géométriques

#### `t_sphere` - Sphère
```
Format .rt: sp 0,0,20 20 255,0,0
```
| Champ | Type | Description |
|-------|------|-------------|
| `center` | `t_point3` | Centre |
| `diameter` | `double` | Diamètre |
| `color` | `t_color3` | Couleur RGB |

#### `t_plane` - Plan infini
```
Format .rt: pl 0,0,-10 0,1,0 0,0,225
```
| Champ | Type | Description |
|-------|------|-------------|
| `point` | `t_point3` | Point sur le plan |
| `normal` | `t_vec3` | Normale normalisée [-1,1] |
| `color` | `t_color3` | Couleur RGB |

#### `t_cylinder` - Cylindre
```
Format .rt: cy 50,0,20.6 0,0,1 14.2 21.42 10,0,255
```
| Champ | Type | Description |
|-------|------|-------------|
| `center` | `t_point3` | Centre |
| `axis` | `t_vec3` | Axe normalisé [-1,1] |
| `diameter` | `double` | Diamètre |
| `height` | `double` | Hauteur |
| `color` | `t_color3` | Couleur RGB |

---

### Conteneurs

#### `t_obj_type` - Enum type d'objet
```c
typedef enum e_obj_type
{
    OBJ_SPHERE,
    OBJ_PLANE,
    OBJ_CYLINDER
}   t_obj_type;
```

#### `t_object` - Nœud de liste chaînée
| Champ | Type | Description |
|-------|------|-------------|
| `type` | `t_obj_type` | Type de l'objet |
| `data` | `void *` | Pointeur vers sphere/plane/cylinder |
| `next` | `t_object *` | Objet suivant |

#### `t_scene` - Conteneur principal
| Champ | Type | Description |
|-------|------|-------------|
| `ambient` | `t_ambient` | Lumière ambiante |
| `camera` | `t_camera` | Caméra |
| `lights` | `t_light *` | Tableau de lumières |
| `light_count` | `int` | Nombre de lumières |
| `objects` | `t_object *` | Liste chaînée d'objets |
| `obj_count` | `int` | Nombre d'objets |

---

## Autres structures

#### `t_window` - Fenêtre MLX
| Champ | Type | Description |
|-------|------|-------------|
| `mlx_ptr` | `void *` | Pointeur MLX |
| `win_ptr` | `void *` | Pointeur fenêtre |

#### `t_ray` - Rayon
| Champ | Type | Description |
|-------|------|-------------|
| `origin` | `t_point3` | Origine du rayon |
| `direction` | `t_vec3` | Direction |

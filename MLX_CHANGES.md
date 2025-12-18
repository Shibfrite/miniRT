# MiniLibX & build changes

## 1. minilibx-macos retirée du suivi Git

- Ajout de `minilibx-macos/` dans [.gitignore](.gitignore) pour ne plus versionner la MiniLibX spécifique à macOS.
- Suppression du dossier `minilibx-macos` de l’index Git avec `git rm -r --cached minilibx-macos`.
- Résultat :
  - Le dossier reste présent en local pour la compilation sur macOS.
  - Il n’est plus poussé sur le dépôt distant (seulement présent dans l’historique passé).

## 2. Détection de l’OS dans le Makefile

- Ajout de la détection d’OS :
  - `UNAME_S := $(shell uname -s)`
- Configuration MiniLibX différente selon la plateforme :

### macOS (Darwin)

- Utilise la MiniLibX Swift : `minilibx-macos`.
- Flags principaux :
  - `MLX_DIR := minilibx-macos`
  - `INC_MLX := -I$(MLX_DIR)`
  - `MLX := -L$(MLX_DIR) -lmlx -framework Cocoa -framework Metal -framework MetalKit -framework QuartzCore`
- La règle `CMLX` lance désormais :
  - `make -C minilibx-macos`

### Linux (autres OS)

- Utilise la MiniLibX X11 : `minilibx-linux`.
- Flags principaux :
  - `MLX_DIR := minilibx-linux`
  - `INC_MLX := -I$(MLX_DIR)`
  - `MLX := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm`

## 3. Chemins d’includes

- La variable `INC` du Makefile a été mise à jour pour utiliser le bon répertoire MLX :
  - `INC := -I$(INC_DIR) $(INC_MLX) -I$(LIBFT_DIR)/$(INC_DIR)`
- Cela permet au `#include "mlx.h"` dans [includes/minirt.h](includes/minirt.h) de fonctionner à la fois sur macOS et sur Linux (à condition que la MiniLibX correspondante soit présente).

## 4. Résultat

- `make re` fonctionne maintenant sur macOS en compilant automatiquement la MiniLibX locale dans `minilibx-macos`.
- Le dépôt Git reste propre : aucun binaire ni code propriétaire de la MiniLibX macOS n’est poussé sur le remote.

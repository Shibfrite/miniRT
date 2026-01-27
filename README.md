# miniRT
Project:			Raytracer
Language:			C
Graphic library:	minilibx
Made by:			makurek (aka Shibfrite), xxxx
Project origin:		42 school program

The raytracer logic comes from "raytracer in one weekend" online book.
It was readapted from C++ to C using minilibx and to satisfy different 42 requirements.
ignored chapters:
6.3 An Abstraction for Hittable Objects.
	Irrelevant in C, apart from the modified hit function.
6.4 Front Faces Versus Back Faces.
10. Metal
11. Dielectrics
13. Defocus blur
We aren't required to have different materials, hence every object will be matte.

Execution:
We view scenes from a viewport, which is the 2D screen that shows us the 3D scene in front of the camera.
From the camera each pixel sends a ray onto the viewport which gives us it's color at each point.
The viewport's dimensions match how many pixels we render.
The scene is composed of objects.
For each ray we calculate if it intersects a shape.
If it does, we keep the point with which it intersected first.
Anti-aliasing:
For each point intersecting a ray we send multiple rays and average their color.

To calculate the color of each point we take into account direct and indirect light.
Direct light comes from light sources + ambiant light.
We cast rays to the light and check if it hits anything.
Indirect light is light bouncing from other objects.
We cast rays into the scene from the given point along the normal of the surface.

From parsing to execution:
The color and intensity of light must be passed into normalise_light() and stored into light.color.
The color of object should be divided by 255 to normalise them before storing them.


---V2

*This project has been created as part of the 42 curriculum by makurek, anpayot.*

---

# miniRT 🌐

A minimal raytracer built from scratch in C, capable of rendering 3D scenes with spheres, planes, and cylinders.

---

## Description

**miniRT** is a simple raytracing engine that generates images from scene descriptions. It demonstrates fundamental computer graphics concepts including:

- **Ray-object intersection** algorithms (sphere, plane, cylinder)
- **Phong illumination model** (ambient + diffuse lighting)
- **Shadow casting** for realistic depth perception
- **Camera projection** with configurable field of view

The program reads a `.rt` scene file describing objects, lights, and camera position, then renders the scene to a window using the MiniLibX graphics library.

### Features

| Feature | Description |
|---------|-------------|
| 🔵 Spheres | Perfect spheres with position, diameter, and color |
| 🟫 Planes | Infinite planes with position, normal, and color |
| 🟠 Cylinders | Finite cylinders with caps, position, axis, diameter, height |
| 💡 Lighting | Ambient light + point light with shadows |
| 📷 Camera | Configurable position, orientation, and FOV |

---

## Instructions

### Prerequisites

- **OS**: Linux (tested on Ubuntu 20.04+)
- **Compiler**: `cc` (clang or gcc)
- **Libraries**: X11, Xext, math library

```bash
# Install dependencies (Debian/Ubuntu)
sudo apt-get install libx11-dev libxext-dev
```

### Compilation

```bash
# Clone the repository
git clone <repository-url>
cd miniRT

# Compile
make

# Clean
make clean    # Remove object files
make fclean   # Remove all generated files
make re       # Recompile from scratch
```

### Execution

```bash
# Run with a scene file
./miniRT scenes/basic_sphere.rt

# Other example scenes
./miniRT scenes/multiple_objects.rt
./miniRT scenes/multiple_cylinder.rt
```

### Controls

| Key | Action |
|-----|--------|
| `ESC` | Close the window |
| `X` (window) | Close the window |

---

## Scene File Format (.rt)

Scene files use a simple text format:

```bash
# Ambient light: A <ratio 0-1> <color R,G,B>
A 0.2 255,255,255

# Camera: C <position x,y,z> <direction x,y,z> <FOV 0-180>
C 0,0,-10 0,0,1 70

# Light: L <position x,y,z> <brightness 0-1> <color R,G,B>
L -10,10,-10 0.8 255,255,255

# Sphere: sp <center x,y,z> <diameter> <color R,G,B>
sp 0,0,5 2 255,0,0

# Plane: pl <point x,y,z> <normal x,y,z> <color R,G,B>
pl 0,-1,0 0,1,0 100,100,100

# Cylinder: cy <center x,y,z> <axis x,y,z> <diameter> <height> <color R,G,B>
cy 2,0,5 0,1,0 1 3 0,255,0
```

---

## Project Structure

```
miniRT/
├── includes/           # Header files
│   ├── minirt.h        # Main header
│   ├── parser.h        # Parsing structures
│   ├── exec.h          # Execution structures
│   └── vec3.h          # Vector math
├── sources/
│   ├── parse/          # Scene file parsing
│   └── exec/           # Raytracing engine
├── libft/              # Custom C library
├── minilibx-linux/     # Graphics library
├── scenes/             # Example scene files
└── docs/               # Documentation
    ├── PARSING_GUIDE.md
    └── EXEC_GUIDE.md
```

---

## Resources

### Documentation & References

- [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) - Peter Shirley's excellent raytracing tutorial
- [Scratchapixel](https://www.scratchapixel.com/) - Comprehensive computer graphics lessons
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Graphics library reference
- [Wikipedia: Ray tracing](https://en.wikipedia.org/wiki/Ray_tracing_(graphics)) - General concepts

### AI Usage

AI tools (GitHub Copilot) were used for:

| Task | Description |
|------|-------------|
| **Documentation** | Generating this README and the guides in `docs/` |
| **Debugging** | Identifying issues (camera orientation, valgrind errors) |
| **Code review** | Checking for forbidden functions and norm compliance |
| **Scene files** | Creating and fixing `.rt` test scenes |

**Core implementation** (parsing, raytracing algorithms, intersection math) was written by the team members.

---

## Authors

- **makurek** - Raytracing engine, rendering
- **anpayot** - Parsing, scene validation

---

## License

This project is part of the 42 school curriculum. Feel free to use it for learning purposes.
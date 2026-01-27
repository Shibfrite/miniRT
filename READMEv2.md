# miniRT 🌐

*This project has been created as part of the 42 curriculum by makurek, anpayot.*

---

A minimal raytracer built from scratch in C, capable of rendering 3D scenes with spheres, planes, and cylinders.

---

## Description

**miniRT** is a simple raytracing engine that generates images from scene descriptions. It demonstrates fundamental computer graphics concepts including:

- **Ray-object intersection** algorithms (sphere, plane, cylinder)
- **Phong illumination model** (ambient + diffuse lighting)
- **Shadow casting** for realistic depth perception
- **Camera projection** with configurable field of view

The program reads a `.rt` scene file describing objects, lights, and camera position, then renders the scene to a window using the MiniLibX graphics library.

The raytracer logic is based on [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) by Peter Shirley, adapted from C++ to C using MiniLibX to satisfy 42 requirements. Since we aren't required to implement different materials, every object uses matte (Lambertian) shading.

### Features

| Feature | Description |
|---------|-------------|
| 🔵 Spheres | Perfect spheres with position, diameter, and color |
| 🟫 Planes | Infinite planes with position, normal, and color |
| 🟠 Cylinders | Finite cylinders with caps, position, axis, diameter, height |
| 💡 Lighting | Ambient light + point light with shadows |
| 📷 Camera | Configurable position, orientation, and FOV |
| 🎨 Anti-aliasing | Multiple samples per pixel for smoother edges |

### How It Works

**Viewport & Rays:**
We view scenes through a viewport (the 2D screen showing the 3D scene). From the camera, each pixel sends a ray onto the viewport to determine its color. The viewport dimensions match the rendered pixel count.

**Intersection:**
For each ray, we calculate if it intersects any object (sphere, plane, cylinder). If multiple intersections occur, we keep the closest one.

**Lighting:**
To calculate the color of each point, we consider:
- **Direct light**: Light sources + ambient light. We cast shadow rays to check if the point is occluded.
- **Indirect light**: Light bouncing from surfaces. We cast rays along the surface normal using Lambertian (diffuse) reflection.

**Anti-aliasing:**
For smoother edges, we send multiple rays per pixel and average their colors.

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
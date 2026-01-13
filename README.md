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

# miniRT
Project:			Raytracer
Language:			C
Graphic library:	minilibx
Made by:			makurek (Shibfrite), xxxx
Project origin:		42 school program

Exec note:
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
We have can change fovs.

Temp note:
Need to implement:
	light sources

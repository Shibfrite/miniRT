//-------------Header-protection-------------
#pragma once

//-------------Includes-------------
#include <stdio.h>
//perror, printf

#include <math.h>
//sqrt

#include <fcntl.h>
//open

#include <stdlib.h>
//malloc, free, exit

#include <unistd.h>
//close, read, write

#include <string.h>
//strerror

#include <sys/time.h>
//gettimeofday

#include "libft.h"
//not yet used

//mlx functons
#include "mlx.h"

// Keycodes et includes spécifiques à l'OS
#ifdef __APPLE__
    // macOS - pas besoin de X11
    #define KEY_ESC 53
    #define KEY_W 13
    #define KEY_A 0
    #define KEY_S 1
    #define KEY_D 2
    #define KEY_UP 126
    #define KEY_DOWN 125
    #define KEY_LEFT 123
    #define KEY_RIGHT 124
#else
    // Linux - X11 requis
    #include <X11/X.h>
    #include <X11/keysym.h>
    #define KEY_ESC 65307
    #define KEY_W 119
    #define KEY_A 97
    #define KEY_S 115
    #define KEY_D 100
    #define KEY_UP 65362
    #define KEY_DOWN 65364
    #define KEY_LEFT 65361
    #define KEY_RIGHT 65363
#endif

//vec3 functions
#include "vec3.h"

//-------------Defines-------------
//Return values
#define SUCCESS 0
#define FAILURE 1

//Window settings
#define WIN_WIDTH 500
#define WIN_ASPECT_RATIO (16.0f/9.0f)
#define WIN_NAME "miniRT"

//Camera settings
//default values
#define FOCAL_LENGTH 1
//Indexes of dimensional arrays
#define WIDTH 0
#define HEIGHT 1

//-------------Structures-------------
//Contains window data for the mlx
typedef struct s_window
{
	void			*mlx_ptr;
	void			*win_ptr;
}	t_window;

//those are equivalent, an array of 3 double.
typedef t_vec3	t_point3;
typedef t_vec3	t_color3;

//rays
typedef struct s_ray
{
	t_point3	origin;
	t_vec3		direction;
}	t_ray;

//-------------Scene elements (from .rt file)-------------

// Ambient light: A 0.2 255,255,255
typedef struct s_ambient
{
	double		ratio;		// [0.0, 1.0]
	t_color3	color;		// RGB [0-255]
	int			is_set;		// unique, must be set once
}	t_ambient;

// Camera: C -50,0,20 0,0,1 70
typedef struct s_camera
{
	t_point3	pos;		// position
	t_vec3		dir;		// normalized orientation [-1,1]
	double		fov;		// field of view [0-180]
	int			is_set;		// unique, must be set once
	// Computed values for rendering
	unsigned int	image_dimension[2];
	t_vec3			viewport_dimension[2];
	t_vec3			pixel_length[2];
	t_point3		first_pixel_location;
	float			aspect_ratio;
}	t_camera;

// Light: L -40,50,0 0.6 255,255,255
typedef struct s_light
{
	t_point3	pos;
	double		brightness;	// [0.0, 1.0]
	t_color3	color;		// RGB (bonus, default white)
}	t_light;

// Sphere: sp 0,0,20 20 255,0,0
typedef struct s_sphere
{
	t_point3	center;
	double		diameter;
	t_color3	color;
}	t_sphere;

// Plane: pl 0,0,-10 0,1,0 0,0,225
typedef struct s_plane
{
	t_point3	point;
	t_vec3		normal;		// normalized [-1,1]
	t_color3	color;
}	t_plane;

// Cylinder: cy 50,0,20.6 0,0,1 14.2 21.42 10,0,255
typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		axis;		// normalized [-1,1]
	double		diameter;
	double		height;
	t_color3	color;
}	t_cylinder;

// Object type enum
typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_obj_type;

// Generic object (linked list node)
typedef struct s_object
{
	t_obj_type		type;
	void			*data;		// ptr to sphere/plane/cylinder
	struct s_object	*next;
}	t_object;

// Main scene container
typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		*lights;		// array
	int			light_count;
	t_object	*objects;		// linked list
	int			obj_count;
}	t_scene;

//-------------Files and functions-------------
//main.c
int			main(void);

//libx.c
t_window	*create_window(unsigned int width, unsigned int height);
int			close_program(void *param);

//input.c
int			mouse_hook(int button, int x, int y, t_window *min_max);
int			key_hook(int keycode, t_window *min_max);

//put_image.c
t_camera	create_camera(unsigned int image_width, unsigned int image_height);
void		render_image(t_window *window, t_camera camera);

//rays.c
t_ray		ray_init(t_point3 origin, t_vec3 direction);
t_point3	at(t_ray ray, double t);

//colors.c
int compute_pixel_color(int x, int y, t_camera camera);

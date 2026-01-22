/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   minirt.h                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/05 18:07:53 by makurek        #+#    #+#                */
/*   Updated: 2026/01/22 13:45:30 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

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

// mlx functions (optional)
// Define USE_MINILIBX when building the full graphical program so the
// real MiniLibX headers are included. For parsing-only builds this
// header may be omitted to avoid requiring the library at compile time.
#ifdef USE_MINILIBX
# include "mlx.h"
# include <X11/X.h>
# include <X11/Xlib.h>
#endif

//vec3 functions
#include "vec3.h"

//bool values
#include "stdbool.h"

//-------------Defines-------------
//Return values
#define SUCCESS 0
#define FAILURE 1

// single-keycode definition (use Linux value by default)
#define KEY_ESCAPE 65307

//Window settings
#define WIN_WIDTH 500
// 16:9
#define WIN_ASPECT_RATIO 1.777f
#define WIN_NAME "miniRT"

//Camera settings
//default values
#define FOCAL_LENGTH 1
//Indexes of dimensional arrays
#define WIDTH 0
#define HEIGHT 1

//Quality of render
#define MAX_DEPTH 10
#define SAMPLES_PER_PIXEL 10

//-------------Structures-------------
//Contains window data for the mlx
typedef struct s_window
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*image;
}	t_window;

//Image data
typedef struct s_imgmeta
{
	int	bpp;
	int	line_length;
	int	endian;
}	t_imgmeta;

typedef t_vec3				t_point3;
typedef t_vec3				t_color3;

//intervals
typedef struct s_interval
{
	double	min;
	double	max;
}	t_interval;

//rays
typedef struct s_ray
{
	t_point3	origin;
	t_vec3		direction;
}	t_ray;

//camera
typedef struct s_camera
{
	unsigned int	image_dimension[2];
	t_vec3			viewport_dimension[2];
	t_vec3			pixel_length[2];
	t_point3		camera_center;
	float			aspect_ratio;
	t_point3		first_pixel_location;
	unsigned int	vertical_fov;
	t_point3		position;
	t_point3		axis;
	t_vec3			view_up;
}	t_camera;

//data of rays hitting a surface
typedef struct s_hit_record
{
	t_point3	p;
	t_color3	color;
	t_vec3		normal;
	double		t;
}	t_hit_record;

//identification
typedef enum s_object_type
{
	OBJ_NULL,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_object_type;

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
}	t_sphere;

typedef struct s_plane
{
	t_point3	base;
	t_vec3		normal;
}	t_plane;

typedef struct s_cylinder
{
	t_point3	center;
	double		radius;
	double		height;
	t_vec3		normal;
}	t_cylinder;

typedef union s_object
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_object;

typedef struct s_interval	t_interval;

typedef struct s_hittable	t_hittable;

typedef struct s_hittable
{
	t_object_type	type;
	t_object		shape;
	t_color3		color;
	bool			(*hit)(t_hittable object, const t_ray,
		t_interval, t_hit_record *);
}	t_hittable;

typedef struct s_light
{
	t_point3	pos;
	t_color3	color;
}	t_light;

typedef struct s_lightening
{
	t_light		*lights;
	size_t		lights_count;
	t_color3	ambient;
}	t_lightening;

typedef struct s_world
{
	t_camera		camera;
	t_lightening	lightening;
	t_hittable		*objects;
}	t_world;

//Scene structure for parsing
#define MAX_OBJECTS 128
#define MAX_LIGHTS 16

typedef struct s_camera_spec
{
	t_point3	position;
	t_vec3		orientation;
	double		fov;
	bool		is_set;
}	t_camera_spec;

typedef struct s_ambient
{
	bool		is_set;
	double		ratio;
	t_color3	color;
}	t_ambient;

typedef struct s_scene
{
	t_camera_spec	cam_spec;
	t_ambient		ambient;
	t_light			lights[MAX_LIGHTS];
	size_t			light_count;
	t_hittable		objects[MAX_OBJECTS];
	size_t			object_count;
}	t_scene;

//-------------Files and functions-------------
//main.c
int			main(int argc, char **argv);

//libx.c
t_window	*create_window(unsigned int width, unsigned int height);
int			close_program(void *param);

//input.c
int			mouse_hook(int button, int x, int y, t_window *min_max);
int			key_hook(int keycode, t_window *min_max);

//put_image.c
t_camera	create_camera(unsigned int window_dimensions[2], t_vec3 position,
				t_vec3 axis, unsigned int vertical_fov);
void		*render_image(t_window *window, t_world world);

//rays.c
t_ray		ray_init(t_point3 origin, t_vec3 direction);
t_point3	at(t_ray ray, double t);

//colors.c
int			compute_pixel_color(size_t coordinates[2], t_world world);

//sphere.c
double		compute_root(double h, double a, double c, t_interval ray_t);
t_hittable	create_sphere(t_point3 center, t_color3 color, double radius);
bool		hit_sphere(t_hittable object, const t_ray r, t_interval ray_t,
				t_hit_record *rec);

//plane.c
t_hittable	create_plane(t_point3 base, t_color3 color, t_vec3 normal);
bool		hit_plane(t_hittable object, const t_ray r, t_interval ray_t,
				t_hit_record *rec);

//cylinder.c
t_hittable	create_cylinder(t_point3 center, t_color3 color,
				double *data, t_vec3 normal);
bool		hit_cylinder(t_hittable object, const t_ray r, t_interval ray_t,
				t_hit_record *rec);

//object.c
bool		hit(t_hittable *object, const t_ray r, t_interval ray_t,
				t_hit_record *rec);

//interval.c
t_interval	interval_init(double min, double max);
double		interval_size(t_interval t);
bool		interval_contains(t_interval t, double x);
bool		interval_surrounds(t_interval t, double x);
double		interval_clamp(t_interval t, double x);

//light.c
t_color3	shade_light(t_point3 p, t_vec3 normal,
				t_light light, t_hittable *objects);

//utils.c
double		degrees_to_radians(double d);
double		random_double(void);
double		random_double_range(double min, double max);
t_vec3		project_on_axis(t_vec3 v, t_vec3 axis);

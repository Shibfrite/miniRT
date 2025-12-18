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
#include <X11/X.h>
#include <X11/Xlib.h>

//vec3 functions
#include "vec3.h"

//bool values
#include "stdbool.h"

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
	void			*image;
}	t_window;

//those are equivalent, an array of 3 int.
typedef t_vec3	t_point3;
typedef t_vec3	t_color3;

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
}	t_camera;

//data of rays hitting a surface
typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		t;
}	t_hit_record;

//Currently used structs to store object data
//Note:
//It might be cleaner to have an abstraction for object
//But premature abstraction is bad

//identification
typedef enum s_object_type
{
	OBJ_NULL,
	OBJ_SPHERE,
	OBJ_PLANE
}	t_object_type;

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
}	t_sphere;

typedef union s_object
{
	t_sphere sphere;
}	t_object;

typedef struct s_interval t_interval;

typedef struct s_hittable
{
    t_object_type	type; //is the type necessary?
	t_object		shape;
	bool			(*hit)(const t_point3, double, const t_ray, t_interval, t_hit_record*);
}	t_hittable;

typedef struct s_hittable_list
{
	t_hittable	*hittable;
	size_t		n_obj;
}	t_hittable_list;

/*
//Hypothetical struct for any object
typedef struct s_object
{
	t_point3		position;
	t_color3		color;
	unsigned int	diameter;
	unsigned int	height;
	int				value;
}	t_object;
*/

/*
 * interval class in cpp for reference
 * every function will be done manually as they are quite simple
class interval {
  public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {} // Default interval is empty

    interval(double min, double max) : min(min), max(max) {}

    double size() const {
        return max - min;
    }

    bool contains(double x) const {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }

    static const interval empty, universe;
};

const interval interval::empty    = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);
*/
typedef struct s_interval
{
	double	min;
	double	max;
} t_interval;	

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
void		*render_image(t_window *window, t_camera camera, t_hittable *objects);

//rays.c
t_ray		ray_init(t_point3 origin, t_vec3 direction);
t_point3	at(t_ray ray, double t);

//colors.c
int			compute_pixel_color(int x, int y, t_camera camera, t_hittable *objects);

//sphere.c
bool		hit_sphere(const t_point3 center, double radius,
                       const t_ray r, t_interval ray_t,
                       t_hit_record *rec);
t_hittable	create_sphere(t_point3 center, double radius);

//object.c
bool		hit(t_hittable *object, const t_ray r, t_interval ray_t, t_hit_record *rec);

//interval.c
t_interval  interval_init(double min, double max);
double	interval_size(t_interval t);
bool	interval_contains(t_interval t, double x);
bool	interval_surrounds(t_interval t, double x);

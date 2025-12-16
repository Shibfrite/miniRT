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

//Hypothetical struct for any object
typedef struct s_object
{
	t_point3		position;
	t_color3		color;
	unsigned int	diameter;
	unsigned int	height;
	int				value;
}	t_object;

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
void		*render_image(t_window *window, t_camera camera);

//rays.c
t_ray		ray_init(t_point3 origin, t_vec3 direction);
t_point3	at(t_ray ray, double t);

//colors.c
int compute_pixel_color(int x, int y, t_camera camera);

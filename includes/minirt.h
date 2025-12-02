//Header-protection
#pragma once

//Includes
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include "libft.h"
#include "mlx.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include "vec3.h"

//Defines
//Return values
#define SUCCESS 0
#define FAILURE 1
//Window settings
#define WIN_HEIGHT 500
#define WIN_WIDTH 500
#define WIN_NAME "miniRT"

//Structures
typedef struct s_window
{
	void			*mlx_ptr;
	void			*win_ptr;
}	t_window;

typedef t_vec3 t_point3;

typedef struct s_object
{
	t_point3		position;
	unsigned int	color[3];
	unsigned int	diameter;
	unsigned int	height;
	int	value;
} t_object;

//Files and functions
//main.c
int	main(void);

//libx.c
t_window	*create_window(void);
int			close_program(void *param);

//input.c
int		mouse_hook(int button, int x, int y, t_window *min_max);
int		key_hook(int keycode, t_window *min_max);

//put_image.c
void	render_image(t_window *window);

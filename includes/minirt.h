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

//Defines
//Return values
#define SUCCESS 0
#define FAILURE 1
//Window settings
#define WIN_HEIGHT 500
#define WIN_WIDTH 500
#define WIN_NAME "miniRT"

//Structures
typedef struct s_window_ctrl
{
	void			*mlx_ptr;
	void			*win_ptr;
}	t_window_ctrl;

//Files and functions
//main.c
int	main(void);

//libx.c
t_window_ctrl	*manage_mlx(char **av);
void			close_program(t_window_ctrl *win_var);

//input.c
int mouse_hook(int button, int x, int y, t_window_ctrl *min_max);
int key_hook(int keycode, t_window_ctrl *min_max);

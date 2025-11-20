#include "minirt.h"

static void	initialize_mlx_resources(void **mlx_ptr, void **win_ptr)
{
	*mlx_ptr = mlx_init();
	if (!(*mlx_ptr))
		exit(1);
	*win_ptr = mlx_new_window(*mlx_ptr, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	if (!(*win_ptr))
	{
		mlx_destroy_display(*mlx_ptr);
		free(*mlx_ptr);
		exit(1);
	}
}

t_window_ctrl	*manage_mlx(char **av)
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_window_ctrl	win_var;

	initialize_mlx_resources(&mlx_ptr, &win_ptr);
	init_win_var(&win_var, mlx_ptr, win_ptr);
	//start program function
	mlx_key_hook(win_ptr, key_hook, &win_var);
	mlx_mouse_hook(win_ptr, mouse_hook, &win_var);
	mlx_hook(win_ptr, DestroyNotify, StructureNotifyMask,
		close_program, &win_var);
	mlx_loop(mlx_ptr);
}

void	close_program(t_fractol *win_var)
{
	if (win_var->win_ptr)
		mlx_destroy_window(win_var->mlx_ptr, win_var->win_ptr);
	if (win_var->mlx_ptr)
	{
		mlx_destroy_display(win_var->mlx_ptr);
		free(win_var->mlx_ptr);
	}
	exit(SUCCESS);
}

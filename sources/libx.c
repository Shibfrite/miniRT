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

static t_window	*init_window(void *mlx_ptr, void *win_ptr)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	window->mlx_ptr = mlx_ptr;
	window->win_ptr = win_ptr;
	return (window);
}

t_window	*create_window(void)
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_window	*window;

	initialize_mlx_resources(&mlx_ptr, &win_ptr);
	window = init_window(mlx_ptr, win_ptr);
	mlx_key_hook(win_ptr, key_hook, window);
	mlx_mouse_hook(win_ptr, mouse_hook, window);
	mlx_hook(win_ptr, DestroyNotify, StructureNotifyMask,
		close_program, window);
	return (window);
}

int	close_program(void *param)
{
	t_window	*window;

	window = (t_window *)param;
	if (window->win_ptr)
		mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	if (window->mlx_ptr)
	{
		mlx_destroy_display(window->mlx_ptr);
		free(window->mlx_ptr);
	}
	free(window);
	exit(SUCCESS);
}

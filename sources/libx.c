/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:08:46 by makurek           #+#    #+#             */
/*   Updated: 2026/01/27 15:23:20 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	initialize_mlx_resources(void **mlx_ptr, void **win_ptr,
		unsigned int width, unsigned int height)
{
	*mlx_ptr = mlx_init();
	if (!(*mlx_ptr))
		exit(1);
	*win_ptr = mlx_new_window(*mlx_ptr, width, height, WIN_NAME);
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

t_window	*create_window(unsigned int width, unsigned int height)
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_window	*window;

	initialize_mlx_resources(&mlx_ptr, &win_ptr, width, height);
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
	if (!window)
		return (FAILURE);
	if (window->image)
		mlx_destroy_image(window->mlx_ptr, window->image);
	if (window->win_ptr)
	{
		mlx_clear_window(window->mlx_ptr, window->win_ptr);
		mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	}
	if (window->mlx_ptr)
	{
		mlx_destroy_display(window->mlx_ptr);
		free(window->mlx_ptr);
	}
	free(window);
	exit(EXIT_SUCCESS);
}

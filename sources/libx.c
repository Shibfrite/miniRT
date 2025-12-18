/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:08:46 by makurek           #+#    #+#             */
/*   Updated: 2025/12/18 10:43:06 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Event codes cross-platform
#ifdef __APPLE__
	#define ON_DESTROY 17
	#define DESTROY_MASK 0
#else
	#define ON_DESTROY 17
	#define DESTROY_MASK (1L << 17)
#endif

static void	initialize_mlx_resources(void **mlx_ptr, void **win_ptr,
		unsigned int width, unsigned int height)
{
	*mlx_ptr = mlx_init();
	if (!(*mlx_ptr))
		exit(1);
	*win_ptr = mlx_new_window(*mlx_ptr, width, height, WIN_NAME);
	if (!(*win_ptr))
	{
#ifndef __APPLE__
		mlx_destroy_display(*mlx_ptr);
#endif
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
	mlx_hook(win_ptr, ON_DESTROY, DESTROY_MASK,
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
#ifndef __APPLE__
		mlx_destroy_display(window->mlx_ptr);
#endif
		free(window->mlx_ptr);
	}
	free(window);
	exit(SUCCESS);
}

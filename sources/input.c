/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   input.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/08 18:08:22 by makurek        #+#    #+#                */
/*   Updated: 2026/01/26 15:58:08 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mouse_hook(int button, int x, int y, t_window *window)
{
	(void)button;
	(void)x;
	(void)y;
	(void)window;
	return (SUCCESS);
}

int	key_hook(int keycode, t_window *window)
{
	if (keycode == KEY_ESCAPE)
	{
		close_program(window);
		exit(SUCCESS);
	}
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   input.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/08 18:08:22 by makurek        #+#    #+#                */
/*   Updated: 2025/12/18 12:16:52 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/*
static void	zoom()
{
}
*/

int	mouse_hook(int button, int x, int y, t_window *window)
{
	(void)button;
	(void)x;
	(void)y;
	(void)window;
/*	if (button == 4)
		zoom();
	else if (button == 5)
		zoom();
	else
		return (SUCCESS);
*/	//render
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

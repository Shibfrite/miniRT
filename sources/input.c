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
	if (keycode == 65307)
		close_program(window);
	return (SUCCESS);
}

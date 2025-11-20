#include "minirt.h"
/*
static void	zoom()
{
}
*/

int	mouse_hook(int button, int x, int y, t_window_ctrl *min_max)
{
/*	if (button == 4)
		zoom();
	else if (button == 5)
		zoom();
	else
		return (SUCCESS);
*/	//render
	return (SUCCESS);
}


int	key_hook(int keycode, t_window_ctrl *min_max)
{
	if (keycode == 65307)
		close_program(min_max, 1, 1);
	return (SUCCESS);
}

#include "minirt.h"

int main(void)
{
	t_window *window;
	//parse input
	window = create_window();
	//start simulation
	render_image(window);
	mlx_loop(window->mlx_ptr);
	printf("test");
	close_program(window);
}

#include "minirt.h"

unsigned int	compute_window_height(unsigned int window_width,
		float aspect_ratio)
{
	unsigned int	window_height;

	window_height = roundf(window_width / aspect_ratio);
	if (window_height < 1)
		window_height = 1;
	return (window_height);
}

int	main(void)
{
	t_window		*window;
	t_camera		camera;
	unsigned int	window_width;
	unsigned int	window_height;
	float			aspect_ratio;
	//object array (spheres, planes and cylinders)
	t_hittable		objects[3];

	window_width = WIN_WIDTH;
	aspect_ratio = WIN_ASPECT_RATIO;
	window_height = compute_window_height(window_width, aspect_ratio);
	window = create_window(window_width, window_height);
	camera = create_camera(window_width, window_height);

	objects[1] = create_sphere(vec3_init(0, 0, -1), 0.5);
	objects[0] = create_sphere(vec3_init(0, -100.5, -1), 100);
	ft_bzero(&objects[2], sizeof(objects[2])); //null terminat
	window->image = render_image(window, camera, objects);
	mlx_loop(window->mlx_ptr);
	return (close_program(window));
}

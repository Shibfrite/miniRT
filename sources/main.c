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

// for now the nbr of objects is manually set.
// it must be null terminated
int	main(void)
{
	t_window		*window;
	t_camera		camera;
	unsigned int	window_dimensions[2];
	float			aspect_ratio;
	t_hittable		objects[6];
	t_light			lights[3];
	double			dimensions[2];
	t_world			world;
	t_lightening	lightening;

	//creating the window
	window_dimensions[WIDTH] = WIN_WIDTH;
	aspect_ratio = WIN_ASPECT_RATIO;
	window_dimensions[HEIGHT] = compute_window_height(window_dimensions[WIDTH], aspect_ratio);
	window = create_window(window_dimensions[WIDTH], window_dimensions[HEIGHT]);

	//creating the world
	camera = create_camera(window_dimensions, vec3_init(-2, 2, 1), vec3_init(2.0/3.0, -2.0/3.0, -1.0/3.0), 90);
	ft_bzero(objects, sizeof(objects));
	objects[0] = create_sphere(vec3_init(0, -100.5, -1), (t_color3)vec3_init(1, 1, 1), 100);
	objects[1] = create_sphere(vec3_init(0, 0, -1.2), (t_color3)vec3_init(0.1, 0.2, 0.5), 0.5);
	objects[2] = create_sphere(vec3_init(-1, 0, -1), (t_color3)vec3_init(0, 0, 0), 0.5);
	dimensions[WIDTH] = 1;
	dimensions[HEIGHT] = 1;
	objects[3] = create_cylinder(vec3_init(-1, 0, -1.5), (t_color3)vec3_init(0.8, 0.8, 1), dimensions, vec3_init(0, 1, 0));
	//objects[3] = create_plane(vec3_init(-1, 0, -1.5), (t_color3)vec3_init(0.8, 0.8, 1), vec3_init(1, 0, 0));
	//objects[4] = create_plane(vec3_init(0, -2, 0), (t_color3)vec3_init(1, 0, -1), vec3_init(0, 0, 1));
	ft_bzero(lights, sizeof(lights));
	lights[0] = (t_light){vec3_init(5, 5, 5), vec3_init(4, 0, 0)};
	lights[1] = (t_light){vec3_init(-5, 5, -5), vec3_init(0, 5, 0)};
	lightening.lights = lights;
	lightening.lights_count = 2;
	lightening.ambient = vec3_init(0, 0, 0);
	world.camera = camera;
	world.lightening = lightening;
	world.objects = objects;

	//generating the image
	window->image = render_image(window, world);
	mlx_loop(window->mlx_ptr);
	return (close_program(window));
}

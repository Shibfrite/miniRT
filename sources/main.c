/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   main.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/26 15:51:04 by makurek        #+#    #+#                */
/*   Updated: 2026/01/26 15:51:06 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

unsigned int	compute_window_height(unsigned int window_width,
		float aspect_ratio)
{
	unsigned int	window_height;

	window_height = roundf(window_width / aspect_ratio);
	if (window_height < 1)
		window_height = 1;
	return (window_height);
}

int	main(int argc, char **argv)
{
	t_window		*window;
	unsigned int	window_dimensions[2];
	float			aspect_ratio;
	t_scene			scene;
	t_world			world;

	if (argc != 2)
	{
		ft_putendl_fd(ERR_USAGE, 2);
		return (FAILURE);
	}
	ft_bzero(&scene, sizeof(t_scene));
	if (parse_scene(&scene, argv[1]) == FAILURE)
		return (FAILURE);
	window_dimensions[WIDTH] = WIN_WIDTH;
	aspect_ratio = WIN_ASPECT_RATIO;
	window_dimensions[HEIGHT] = compute_window_height(window_dimensions[WIDTH],
			aspect_ratio);
	window = create_window(window_dimensions[WIDTH], window_dimensions[HEIGHT]);
	world = scene_to_world(&scene, window_dimensions);
	window->image = render_image(window, world);
	mlx_loop(window->mlx_ptr);
	return (close_program(window));
}

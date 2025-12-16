/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   put_image.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/08 17:58:26 by makurek        #+#    #+#                */
/*   Updated: 2025/12/11 15:24:41 by makurek        ########   odam.nl        */
/*																			*/
/* ************************************************************************** */

#include "minirt.h"

/*
	Interface to use the mlx_get_data_addr function
*/
static char	*get_image_data(void *img)
{
	int	bpp;
	int	line_length;
	int	endian;

	return (mlx_get_data_addr(img, &bpp, &line_length, &endian));
}

/*
 	locates the first pixel of the viewport, at the top left.

	the calculation done is as follows:

		viewport_upper_left = camera_center - vec3(0, 0, focal_length)
							- viewport_u/2 - viewport_v/2;

		pixel00_loc = viewport_upper_left + 0.5 
					* (pixel_delta_u + pixel_delta_v);
*/
static t_point3	locate_first_pixel(t_point3 camera_center,
								t_vec3 viewport_dimension[2],
									t_vec3 pixel_length[2])
{
	t_point3	viewport_upper_left;
	t_point3	first_pixel_location;
	t_point3	viewport_width;
	t_point3	viewport_height;
	t_vec3		res;

	res = vec3_init(0, 0, FOCAL_LENGTH);
	res = vec3_sub(camera_center, res);
	viewport_width = vec3_div(viewport_dimension[WIDTH], 2.0);
	viewport_height = vec3_div(viewport_dimension[HEIGHT], 2.0);
	res = vec3_sub(res, viewport_width);
	viewport_upper_left = vec3_sub(res, viewport_height);
	res = vec3_add(pixel_length[WIDTH], pixel_length[HEIGHT]);
	res = vec3_scale(res, 0.5);
	first_pixel_location = vec3_add(viewport_upper_left, res);
	return (first_pixel_location);
}

/*
	init the camera structure.
	calculates the viewport's dimensions.
	calculates the dimension the distance between pixels.
*/
t_camera	create_camera(unsigned int image_width, unsigned int image_height)
{
	t_camera	camera;
	float		viewport_height;
	float		viewport_width;

	camera.image_dimension[WIDTH] = image_width;
	camera.image_dimension[HEIGHT] = image_height;
	camera.camera_center = vec3_zero();
	viewport_height = 2.0;
	viewport_width = viewport_height
		* ((double)camera.image_dimension[WIDTH]
			/ camera.image_dimension[HEIGHT]);
	camera.viewport_dimension[WIDTH] = vec3_init(viewport_width, 0, 0);
	camera.viewport_dimension[HEIGHT] = vec3_init(0, -viewport_height, 0);
	camera.pixel_length[WIDTH] = vec3_div(camera.viewport_dimension[WIDTH],
			camera.image_dimension[WIDTH]);
	camera.pixel_length[HEIGHT] = vec3_div(camera.viewport_dimension[HEIGHT],
			camera.image_dimension[HEIGHT]);
	camera.first_pixel_location = locate_first_pixel(camera.camera_center,
			camera.viewport_dimension, camera.pixel_length);
	return (camera);
}

/*
	we pass on each pixel and compute it's color.
*/
static void	render_pixels(void *img, t_camera camera)
{
	unsigned int	*pixels;
	unsigned int	x;
	unsigned int	y;

	pixels = (unsigned int *)get_image_data(img);
	y = 0;
	while (y < camera.image_dimension[HEIGHT])
	{
		x = 0;
		while (x < camera.image_dimension[WIDTH])
		{
			pixels[y * camera.image_dimension[WIDTH] + x]
				= compute_pixel_color(x, y, camera);
			x++;
		}
		y++;
	}
}

/*
	we create an image, fill it and show it.
*/
void	*render_image(t_window *window, t_camera camera)
{
	void	*img;

	img = mlx_new_image(window->mlx_ptr, camera.image_dimension[WIDTH],
			camera.image_dimension[HEIGHT]);
	if (!img)
		close_program(window);
	render_pixels(img, camera);
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, img, 0, 0);
	return (img);
}

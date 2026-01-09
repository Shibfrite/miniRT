/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   put_image.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/08 17:58:26 by makurek        #+#    #+#                */
/*   Updated: 2026/01/09 14:44:20 by makurek        ########   odam.nl        */
/*																			*/
/* ************************************************************************** */

#include "minirt.h"

/*
    Returns the raw pixel buffer pointer from an MLX image.
*/
static char	*get_image_data(void *img)
{
	int	bpp;
	int	line_length;
	int	endian;

	return (mlx_get_data_addr(img, &bpp, &line_length, &endian));
}

/*
    Computes the world‑space position of the top‑left pixel of the viewport.
*/
static t_point3	locate_first_pixel(t_point3 camera_center,
								t_vec3 focal_length,
								t_vec3 viewport_dimension[2],
									t_vec3 pixel_length[2])
{
	t_point3	viewport_upper_left;
	t_point3	first_pixel_location;
	t_point3	viewport_width;
	t_point3	viewport_height;
	t_vec3		res;

	res = vec3_sub(camera_center, focal_length);
	viewport_width = vec3_div(viewport_dimension[WIDTH], 2.0);
	viewport_height = vec3_div(viewport_dimension[HEIGHT], 2.0);
	viewport_upper_left = vec3_sub(vec3_sub(res, viewport_width),
			viewport_height);
	res = vec3_add(pixel_length[WIDTH], pixel_length[HEIGHT]);
	res = vec3_scale(res, 0.5);
	first_pixel_location = vec3_add(viewport_upper_left, res);
	return (first_pixel_location);
}

/*
    Builds the camera: orientation vectors, viewport size,
	pixel spacing, and first‑pixel position.
*/
t_camera	create_camera(unsigned int image_width, unsigned int image_height)
{
	t_camera	camera;
	float		viewport_height;
	float		viewport_width;
	double		theta;
	double		h;
	int			focal_length;
	t_vec3		v;
	t_vec3		w;
	t_vec3		u;

	camera.lookfrom = vec3_init(-2, 2, 1);
	camera.lookat = vec3_init(0, 0, 0);
	camera.view_up = vec3_init(0, 1, 0);
	camera.image_dimension[WIDTH] = image_width;
	camera.image_dimension[HEIGHT] = image_height;
	camera.camera_center = camera.lookfrom;
	camera.vertical_fov = 90;
	focal_length = vec3_length(vec3_sub(camera.lookfrom, camera.lookat));
	theta = degrees_to_radians(camera.vertical_fov);
	h = tan(theta / 2.0);
	viewport_height = 2.0 * h * focal_length;
	viewport_width = viewport_height
		* ((double)camera.image_dimension[WIDTH]
			/ camera.image_dimension[HEIGHT]);
	w = vec3_unit(vec3_sub(camera.lookfrom, camera.lookat));
	u = vec3_unit(vec3_cross(camera.view_up, w));
	v = vec3_cross(w, u);
	camera.viewport_dimension[WIDTH] = vec3_scale(u, viewport_width);
	camera.viewport_dimension[HEIGHT] = vec3_scale(vec3_neg(v),
			viewport_height);
	camera.pixel_length[WIDTH] = vec3_div(camera.viewport_dimension[WIDTH],
			camera.image_dimension[WIDTH]);
	camera.pixel_length[HEIGHT] = vec3_div(camera.viewport_dimension[HEIGHT],
			camera.image_dimension[HEIGHT]);
	camera.first_pixel_location = locate_first_pixel(camera.camera_center,
			vec3_scale(w, focal_length),
			camera.viewport_dimension, camera.pixel_length);
	return (camera);
}

/*
    Iterates over all pixels and writes each computed color
	into the image buffer.
*/
static void	render_pixels(void *img, t_world world)
{
	unsigned int	*pixels;
	size_t			coordinates[2];
	t_camera		camera;

	camera = world.camera;
	pixels = (unsigned int *)get_image_data(img);
	coordinates[1] = 0;
	while (coordinates[1] < camera.image_dimension[HEIGHT])
	{
		coordinates[0] = 0;
		while (coordinates[0] < camera.image_dimension[WIDTH])
		{
			pixels[coordinates[1] * camera.image_dimension[WIDTH]
				+ coordinates[0]]
				= compute_pixel_color(coordinates, world);
			coordinates[0]++;
		}
		coordinates[1]++;
	}
}

/*
    Allocates an MLX image, renders all pixels, and displays it in the window.
*/
void	*render_image(t_window *window, t_world world)
{
	void	*img;

	img = mlx_new_image(window->mlx_ptr, world.camera.image_dimension[WIDTH],
			world.camera.image_dimension[HEIGHT]);
	if (!img)
		close_program(window);
	render_pixels(img, world);
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, img, 0, 0);
	return (img);
}

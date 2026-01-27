/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   put_image.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/08 17:58:26 by makurek        #+#    #+#                */
/*   Updated: 2026/01/26 15:58:32 by makurek        ########   odam.nl        */
/*																			*/
/* ************************************************************************** */

#include "minirt.h"

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
static void	camera_setup_view(t_camera *camera,
				float viewport_height, float viewport_width,
				int focal_length)
{
	t_vec3	w;
	t_vec3	u;
	t_vec3	v;

	w = vec3_neg(camera->axis);
	u = vec3_unit(vec3_cross(camera->view_up, w));
	v = vec3_cross(w, u);
	camera->viewport_dimension[WIDTH] = vec3_scale(u, viewport_width);
	camera->viewport_dimension[HEIGHT] = vec3_scale(vec3_neg(v),
			viewport_height);
	camera->pixel_length[WIDTH] = vec3_div(
			camera->viewport_dimension[WIDTH],
			camera->image_dimension[WIDTH]);
	camera->pixel_length[HEIGHT] = vec3_div(
			camera->viewport_dimension[HEIGHT],
			camera->image_dimension[HEIGHT]);
	camera->first_pixel_location = locate_first_pixel(
			camera->camera_center,
			vec3_scale(w, focal_length),
			camera->viewport_dimension,
			camera->pixel_length);
}

t_camera	create_camera(unsigned int window_dimensions[2], t_vec3 position,
				t_vec3 axis, unsigned int vertical_fov)
{
	t_camera	camera;
	float		viewport_height;
	float		viewport_width;
	double		h;
	int			focal_length;

	camera.position = position;
	camera.axis = axis;
	camera.view_up = vec3_init(0, 1, 0);
	if (fabs(axis.e[1]) > 0.999)
		camera.view_up = vec3_init(0, 0, 1);
	camera.image_dimension[WIDTH] = window_dimensions[WIDTH];
	camera.image_dimension[HEIGHT] = window_dimensions[HEIGHT];
	camera.camera_center = camera.position;
	camera.vertical_fov = vertical_fov;
	focal_length = 1;
	h = tan(degrees_to_radians(camera.vertical_fov) / 2.0);
	viewport_height = 2.0 * h * focal_length;
	viewport_width = viewport_height
		* ((double)camera.image_dimension[WIDTH]
			/ camera.image_dimension[HEIGHT]);
	camera_setup_view(&camera, viewport_height, viewport_width, focal_length);
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
	t_imgmeta		meta;

	camera = world.camera;
	pixels = (unsigned int *)mlx_get_data_addr(img, &meta.bpp,
			&meta.line_length, &meta.endian);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   colors.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/11 12:19:39 by makurek        #+#    #+#                */
/*   Updated: 2026/01/08 15:09:56 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	calculate the color of a single ray.

	the calculation is done as follows:

			unit_direction = unit_vector(r.direction());
			a = 0.5*(unit_direction.y() + 1.0);
			return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
*/
static t_color3	ray_color(const t_ray r, t_hittable *objects, int depth)
{
	double			a;
	t_vec3			term1;
	t_vec3			term2;
	t_hit_record	hit_record;
	t_vec3			dir;

	if (depth <= 0)
		return ((t_color3)vec3_init(0, 0, 0));
	if (hit(objects, r, interval_init(0.001, INFINITY), &hit_record))
	{
		dir = vec3_add(hit_record.normal, random_unit_vector());
		return (vec3_mul(ray_color(ray_init(hit_record.p, dir),
					objects, --depth), hit_record.color));
	}
	a = 0.5 * (vec3_unit(r.direction).e[1] + 1.0);
	term1 = vec3_scale(vec3_init(1.0, 1.0, 1.0), 1.0 - a);
	term2 = vec3_scale(vec3_init(0.5, 0.7, 1.0), a);
	return (vec3_add(term1, term2));
}

t_vec3	sample_square(void)
{
	return (vec3_init(random_double() - 0.5, random_double() - 0.5, 0.0));
}

t_ray	get_ray(t_camera camera, int x, int y)
{
	t_vec3	offset;
	t_vec3	pixel_sample;
	t_vec3	ray_direction;

	offset = sample_square();
	pixel_sample = vec3_add(
			vec3_add(camera.first_pixel_location,
				vec3_scale(camera.pixel_length[WIDTH],
					(double)x + offset.e[0])),
			vec3_scale(camera.pixel_length[HEIGHT], (double)y + offset.e[1]));
	ray_direction = vec3_sub(pixel_sample, camera.camera_center);
	return (ray_init(camera.camera_center, ray_direction));
}

static double	linear_to_gamma(double linear_component)
{
	if (linear_component > 0.0)
		return (sqrt(linear_component));
	return (0.0);
}

/*
	calculates the color of a single pixel.

	Each pixel is defined as a ray.
	We first calculate the data of each ray.
	Meaning it's starting position (pixel_center),
	And it's direction (ray_direction).
	Then we call ray_color to actually compute the color
	We normalise it by using the scale 0-255 instead of 0-1.
	We bitshift for the format requirement.
*/
int	compute_pixel_color(int x, int y, t_camera camera, t_hittable *objects)
{
	t_interval		intensity;
	t_color3		color;
	unsigned int	normalised_color[3];
	int				sample;

	sample = 0;
	color = vec3_init(0, 0, 0);
	while (sample++ < SAMPLES_PER_PIXEL)
		color = vec3_add(color, ray_color(get_ray(camera, x, y),
					objects, MAX_DEPTH));
	vec3_div_inplace(&color, SAMPLES_PER_PIXEL);
	intensity = interval_init(0.000, 0.999);
	normalised_color[0] = 256 * linear_to_gamma(
			interval_clamp(intensity, color.e[0]));
	normalised_color[1] = 256 * linear_to_gamma(
			interval_clamp(intensity, color.e[1]));
	normalised_color[2] = 256 * linear_to_gamma(
			interval_clamp(intensity, color.e[2]));
	return ((normalised_color[0] << 16) | (normalised_color[1] << 8)
		| normalised_color[2]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   colors.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/11 12:19:39 by makurek        #+#    #+#                */
/*   Updated: 2026/01/09 12:21:48 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
    Computes the radiance along a ray using direct lighting and recursive diffuse bounce.
*/
static t_color3	ray_color(const t_ray r, t_light light, t_hittable *objects,
				int depth)
{
	t_hit_record	rec;
	t_color3		direct;
	t_vec3			bounce_dir;
	t_color3		bounced;

	if (depth <= 0)
		return (vec3_init(0, 0, 0));
	if (!hit(objects, r, interval_init(0.001, INFINITY), &rec))
		return (vec3_init(0, 0, 0));
	light = (t_light){vec3_init(5, 5, 5), vec3_init(4, 4, 4)};
	direct = vec3_mul(rec.color,
			shade_light(rec.p, rec.normal, light, objects));
	bounce_dir = vec3_add(rec.normal, random_unit_vector());
	bounced = vec3_mul(
			ray_color(ray_init(rec.p, bounce_dir), light, objects, depth - 1),
			rec.color);
	return (vec3_add(direct, bounced));
}

/*
    Returns a random 2D offset in a unit square for pixel sampling.
*/
t_vec3	sample_square(void)
{
	return (vec3_init(random_double() - 0.5, random_double() - 0.5, 0.0));
}

/*
    Builds a camera ray through pixel (x,y) with subpixel jitter.
*/
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

/*
    Converts a linear color component to gamma‑corrected space.
*/
static double	linear_to_gamma(double linear_component)
{
	if (linear_component > 0.0)
		return (sqrt(linear_component));
	return (0.0);
}

/*
    Samples multiple rays for a pixel, accumulates color, applies gamma correction, and packs RGB.
*/
int	compute_pixel_color(size_t coordinates[2], t_camera camera, t_light light,
				t_hittable *objects)
{
	t_interval		intensity;
	t_color3		color;
	unsigned int	normalised_color[3];
	int				sample;

	sample = 0;
	color = vec3_init(0, 0, 0);
	while (sample++ < SAMPLES_PER_PIXEL)
		color = vec3_add(color, ray_color(get_ray(camera, coordinates[0],
						coordinates[1]), light, objects, MAX_DEPTH));
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

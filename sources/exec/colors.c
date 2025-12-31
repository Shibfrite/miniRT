/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   colors.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/11 12:19:39 by makurek        #+#    #+#                */
/*   Updated: 2025/12/31 17:09:14 by makurek        ########   odam.nl        */
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
	t_vec3			unit_direction;
	double			a;
	t_vec3			term1;
	t_vec3			term2;
	t_hit_record	hit_record;

	if (depth <= 0)
		return ((t_color3)vec3_init(0, 0, 0));
	if (hit(objects, r, interval_init(0.001, INFINITY), &hit_record))
	{
		t_vec3 dir = vec3_add(hit_record.normal, random_unit_vector());
		return (vec3_scale(ray_color(ray_init(hit_record.p, dir), objects, --depth), 0.5));
	}
	unit_direction = vec3_unit(r.direction);
	a = 0.5 * (unit_direction.e[1] + 1.0);
	term1 = vec3_scale(vec3_init(1.0, 1.0, 1.0), 1.0 - a);
	term2 = vec3_scale(vec3_init(0.5, 0.7, 1.0), a);
	return (vec3_add(term1, term2));
}

t_vec3	sample_square()
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
                 vec3_scale(camera.pixel_length[WIDTH], (double)x + offset.e[0])),
        vec3_scale(camera.pixel_length[HEIGHT], (double)y + offset.e[1])
    );
    ray_direction = vec3_sub(pixel_sample, camera.camera_center);
    return (ray_init(camera.camera_center, ray_direction));
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
	unsigned	red;
	unsigned	blue;
	unsigned	green;
	t_interval	intensity;
	t_color3	color;
	int			samples_per_pixel;
	int			sample;
	int			max_depth;

	samples_per_pixel = 10;
	max_depth = 10;
	sample = 0;
	color = (t_color3)vec3_init(0, 0, 0);
	while (sample++ < samples_per_pixel)
	{
		t_ray	ray = get_ray(camera, x, y);
		color = vec3_add(color, ray_color(ray, objects, max_depth));
	}
	vec3_div_inplace(&color, samples_per_pixel);
	intensity = interval_init(0.000, 0.999);
	red = 256 * interval_clamp(intensity, color.e[0]);
	green = 256 * interval_clamp(intensity, color.e[1]);
	blue = 256 * interval_clamp(intensity, color.e[2]);
	return ((red << 16) | (green << 8) | blue);
}

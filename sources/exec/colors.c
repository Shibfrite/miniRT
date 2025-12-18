/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   colors.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/11 12:19:39 by makurek        #+#    #+#                */
/*   Updated: 2025/12/18 17:25:03 by makurek        ########   odam.nl        */
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
static t_color3	ray_color(const t_ray r, t_hittable *objects)
{
	t_vec3			unit_direction;
	double			a;
	t_vec3			term1;
	t_vec3			term2;
	t_hit_record	hit_record;

	if (hit(objects, r, interval_init(0, INFINITY), &hit_record))
	{
		t_vec3 n = hit_record.normal;
		return (t_color3){0.5*(n.e[0]+1), 0.5*(n.e[1]+1), 0.5*(n.e[2]+1)};
	}
	unit_direction = vec3_unit(r.direction);
	a = 0.5 * (unit_direction.e[1] + 1.0);
	term1 = vec3_scale(vec3_init(1.0, 1.0, 1.0), 1.0 - a);
	term2 = vec3_scale(vec3_init(0.5, 0.7, 1.0), a);
	return (vec3_add(term1, term2));
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
	t_point3	pixel_center;
	t_vec3		ray_direction;
	t_color3	color;
	t_ray		ray;
	t_vec3		res;

	res = vec3_add(vec3_scale(camera.pixel_length[WIDTH], x),
			vec3_scale(camera.pixel_length[HEIGHT], y));
	pixel_center = vec3_add(res, camera.first_pixel_location);
	ray_direction = vec3_sub(pixel_center, camera.camera_center);
	ray = ray_init(camera.camera_center, ray_direction);
	color = ray_color(ray, objects);
	return (((unsigned)(255.999 * color.e[0]) << 16) |
		((unsigned)(255.999 * color.e[1]) << 8) |
		(unsigned)(255.999 * color.e[2]));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   light.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/09 11:38:50 by makurek        #+#    #+#                */
/*   Updated: 2026/01/09 12:27:23 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
    Computes diffuse lighting at point p with shadow checking
	and distance attenuation.
*/
t_color3	shade_light(t_point3 p, t_vec3 normal,
							t_light light, t_hittable *objects)
{
	t_vec3			to_light;
	double			dist2;
	t_vec3			dir;
	t_hit_record	tmp;
	double			n_dot_light;

	to_light = vec3_sub(light.pos, p);
	dist2 = vec3_length_squared(to_light);
	dir = vec3_unit(to_light);
	if (hit(objects, ray_init(p, dir), interval_init(0.001,
				sqrt(dist2)-0.001), &tmp))
		return (vec3_init(0, 0, 0));
	n_dot_light = vec3_dot(normal, dir);
	if (n_dot_light < 0)
		return (vec3_init(0, 0, 0));
	return (vec3_scale(light.intensity, n_dot_light / dist2));
}

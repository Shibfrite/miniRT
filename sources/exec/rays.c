/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   rays.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/08 18:07:29 by makurek        #+#    #+#                */
/*   Updated: 2025/12/08 18:07:47 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_init(t_point3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_point3	at(t_ray ray, double t)
{
	t_vec3	res;

	res = vec3_scale(ray.direction, t);
	return (vec3_add(res, ray.origin));
}

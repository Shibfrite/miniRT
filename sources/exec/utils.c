/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   utils.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/29 17:32:23 by makurek        #+#    #+#                */
/*   Updated: 2026/01/12 11:47:03 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	degrees_to_radians(double d)
{
	return (d * M_PI / 180.0);
}

double	random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

double	random_double_range(double min, double max)
{
	return (min + (max - min) * random_double());
}

t_vec3	project_on_axis(t_vec3 v, t_vec3 axis)
{
	return (vec3_scale(axis, vec3_dot(v, axis)));
}

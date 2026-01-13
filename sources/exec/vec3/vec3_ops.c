/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   vec3_ops.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/12 11:04:52 by makurek        #+#    #+#                */
/*   Updated: 2026/01/12 11:05:14 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* addition */
t_vec3	vec3_add(const t_vec3 u, const t_vec3 v)
{
	return ((t_vec3){u.e[0] + v.e[0],
		u.e[1] + v.e[1],
		u.e[2] + v.e[2]});
}

/* subtraction */
t_vec3	vec3_sub(const t_vec3 u, const t_vec3 v)
{
	return ((t_vec3){u.e[0] - v.e[0],
		u.e[1] - v.e[1],
		u.e[2] - v.e[2]});
}

/* multiplication */
t_vec3	vec3_mul(const t_vec3 u, const t_vec3 v)
{
	return ((t_vec3){u.e[0] * v.e[0],
		u.e[1] * v.e[1],
		u.e[2] * v.e[2]});
}

/* scalar division */
t_vec3	vec3_div(const t_vec3 v, double t)
{
	return (vec3_scale(v, 1.0 / t));
}

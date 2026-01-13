/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   vec3_ops2.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/12 11:06:33 by makurek        #+#    #+#                */
/*   Updated: 2026/01/12 11:06:45 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* scalar multiplication */
t_vec3	vec3_scale(const t_vec3 v, double t)
{
	return ((t_vec3){t * v.e[0],
		t * v.e[1],
		t * v.e[2]});
}

/* dot product */
double	vec3_dot(const t_vec3 u, const t_vec3 v)
{
	return (u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2]);
}

/* cross product */
t_vec3	vec3_cross(const t_vec3 u, const t_vec3 v)
{
	return ((t_vec3){u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]});
}

/* unit vector */
t_vec3	vec3_unit(const t_vec3 v)
{
	return (vec3_div(v, vec3_length(v)));
}

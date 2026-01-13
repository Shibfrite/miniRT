/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   vec3_length.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/12 11:06:59 by makurek        #+#    #+#                */
/*   Updated: 2026/01/12 11:18:23 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

/* length squared */
double	vec3_length_squared(const t_vec3 v)
{
	return (v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2]);
}

/* length */
double	vec3_length(const t_vec3 v)
{
	return (sqrt(vec3_length_squared(v)));
}

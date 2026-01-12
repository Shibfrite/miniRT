/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   vec3_construct.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/12 11:16:45 by makurek        #+#    #+#                */
/*   Updated: 2026/01/12 11:17:26 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

/* init */
t_vec3	vec3_init(double e0, double e1, double e2)
{
	t_vec3	v;

	v.e[0] = e0;
	v.e[1] = e1;
	v.e[2] = e2;
	return (v);
}

/* init to 0 */
t_vec3	vec3_zero(void)
{
	return (vec3_init(0.0, 0.0, 0.0));
}

/* printing */
void	vec3_print(const t_vec3 v)
{
	printf("%f %f %f", v.e[0], v.e[1], v.e[2]);
}

// negate the vector
t_vec3	vec3_neg(t_vec3 v)
{
	return ((t_vec3){-v.e[0], -v.e[1], -v.e[2]});
}

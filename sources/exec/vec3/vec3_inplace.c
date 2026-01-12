/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   vec3_inplace.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/12 11:02:03 by makurek        #+#    #+#                */
/*   Updated: 2026/01/12 11:02:20 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* add by a fix value */
void	vec3_add_inplace(t_vec3 *a, double t)
{
	a->e[0] += t;
	a->e[1] += t;
	a->e[2] += t;
}

/* subtract by a fix value */
void	vec3_sub_inplace(t_vec3 *a, double t)
{
	vec3_add_inplace(a, -t);
}

/* multiply by a fix value */
void	vec3_mul_inplace(t_vec3 *a, double t)
{
	a->e[0] *= t;
	a->e[1] *= t;
	a->e[2] *= t;
}

/* divide by a fix value */
void	vec3_div_inplace(t_vec3 *a, double t)
{
	vec3_mul_inplace(a, 1.0 / t);
}

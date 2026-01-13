/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   vec3_random.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/12 11:09:39 by makurek        #+#    #+#                */
/*   Updated: 2026/01/12 11:19:29 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_vec3	vec3_random(void)
{
	return (vec3_init(random_double(), random_double(), random_double()));
}

t_vec3	vec3_random_range(double min, double max)
{
	return (vec3_init(random_double_range(min, max),
			random_double_range(min, max), random_double_range(min, max)));
}

t_vec3	random_unit_vector(void)
{
	t_vec3	p;
	double	lensq;

	while (true)
	{
		p = vec3_random_range(-1.0, 1.0);
		lensq = vec3_length_squared(p);
		if (lensq > 1e-160 && lensq <= 1.0)
			return (vec3_scale(p, 1.0 / sqrt(lensq)));
	}
}

t_vec3	random_on_hemisphere(const t_vec3 normal)
{
	t_vec3	u;

	u = random_unit_vector();
	if (vec3_dot(u, normal) > 0.0)
		return (u);
	else
		return (vec3_neg(u));
}

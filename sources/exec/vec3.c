/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   vec3.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/29 17:35:29 by makurek        #+#    #+#                */
/*   Updated: 2025/12/29 17:35:31 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

/* printing */
void	vec3_print(const t_vec3 v)
{
	printf("%f %f %f", v.e[0], v.e[1], v.e[2]);
}

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

/* scalar multiplication */
t_vec3	vec3_scale(const t_vec3 v, double t)
{
	return ((t_vec3){t * v.e[0],
		t * v.e[1],
		t * v.e[2]});
}

/* scalar division */
t_vec3	vec3_div(const t_vec3 v, double t)
{
	return (vec3_scale(v, 1.0 / t));
}

// negate the vector
t_vec3	vec3_neg(t_vec3 v)
{
	return ((t_vec3){-v.e[0], -v.e[1], -v.e[2]});
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

/* unit vector */
t_vec3	vec3_unit(const t_vec3 v)
{
	return (vec3_div(v, vec3_length(v)));
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   vec3.h                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/08 18:33:11 by makurek        #+#    #+#                */
/*   Updated: 2026/01/12 11:31:09 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/* 3D vector type */
typedef struct s_vec3
{
	double	e[3];
}	t_vec3;

/* vec3_construct.c */
t_vec3  vec3_init(double e0, double e1, double e2);
t_vec3  vec3_zero(void);
t_vec3  vec3_neg(t_vec3 v);
void    vec3_print(const t_vec3 v);

/* vec3_inplace.c */
void    vec3_add_inplace(t_vec3 *a, double t);
void    vec3_sub_inplace(t_vec3 *a, double t);
void    vec3_mul_inplace(t_vec3 *a, double t);
void    vec3_div_inplace(t_vec3 *a, double t);

/* vec3_ops.c */
t_vec3  vec3_add(const t_vec3 u, const t_vec3 v);
t_vec3  vec3_sub(const t_vec3 u, const t_vec3 v);
t_vec3  vec3_mul(const t_vec3 u, const t_vec3 v);
t_vec3  vec3_scale(const t_vec3 v, double t);

/* vec3_ops2.c */
t_vec3  vec3_div(const t_vec3 v, double t);
double  vec3_dot(const t_vec3 u, const t_vec3 v);
t_vec3  vec3_cross(const t_vec3 u, const t_vec3 v);
t_vec3  vec3_unit(const t_vec3 v);

/* vec3_length.c */
double  vec3_length(const t_vec3 v);
double  vec3_length_squared(const t_vec3 v);

/* vec3_random.c */
t_vec3  vec3_random(void);
t_vec3  vec3_random_range(double min, double max);
t_vec3  random_unit_vector(void);
t_vec3  random_on_hemisphere(const t_vec3 normal);

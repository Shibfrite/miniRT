/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                              :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:07:53 by makurek           #+#    #+#             */
/*   Updated: 2026/01/22 13:35:24 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

//-------------Header-protection-------------
#pragma once

//-------------Includes-------------
#include "minirt.h"

//-------------Structures-------------

typedef t_vec3	t_point3;
typedef t_vec3	t_color3;

//intervals
typedef struct s_interval
{
	double	min;
	double	max;
}	t_interval;

//rays
typedef struct s_ray
{
	t_point3	origin;
	t_vec3		direction;
}	t_ray;

//data of rays hitting a surface
typedef struct s_hit_record
{
	t_point3	p;
	t_color3	color;
	t_vec3		normal;
	double		t;
}	t_hit_record;

//-------------Files and functions-------------

//rays.c
t_ray		ray_init(t_point3 origin, t_vec3 direction);
t_point3	at(t_ray ray, double t);

//colors.c
int			compute_pixel_color(size_t coordinates[2], t_world world);

//sphere.c
double		compute_root(double h, double a, double c, t_interval ray_t);
t_hittable	create_sphere(t_point3 center, t_color3 color, double radius);
bool		hit_sphere(t_hittable object, const t_ray r, t_interval ray_t,
				t_hit_record *rec);

//plane.c
t_hittable	create_plane(t_point3 base, t_color3 color, t_vec3 normal);
bool		hit_plane(t_hittable object, const t_ray r, t_interval ray_t,
				t_hit_record *rec);

//cylinder.c
t_hittable	create_cylinder(t_point3 center, t_color3 color,
				double *data, t_vec3 normal);
bool		hit_cylinder(t_hittable object, const t_ray r, t_interval ray_t,
				t_hit_record *rec);

//object.c
bool		hit(t_hittable *object, const t_ray r, t_interval ray_t,
				t_hit_record *rec);

//interval.c
t_interval	interval_init(double min, double max);
double		interval_size(t_interval t);
bool		interval_contains(t_interval t, double x);
bool		interval_surrounds(t_interval t, double x);
double		interval_clamp(t_interval t, double x);

//light.c
t_color3	shade_light(t_point3 p, t_vec3 normal,
				t_light light, t_hittable *objects);

//utils.c
double		degrees_to_radians(double d);
double		random_double(void);
double		random_double_range(double min, double max);
t_vec3		project_on_axis(t_vec3 v, t_vec3 axis);

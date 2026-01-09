/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   plane.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/06 16:24:59 by makurek        #+#    #+#                */
/*   Updated: 2026/01/09 14:43:33 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	calculates if a ray intersects an infinite plane

	a plane is defined by a point Q and a normal N:
		dot(N, P) = dot(N, Q)

	a ray is:
		R(t) = O + t·D

	substitute R(t) into the plane equation and solve for t:
		t = (dot(N, Q) - dot(N, O)) / dot(N, D)

	if dot(N, D) ≈ 0 the ray is parallel → no hit
	if t is outside the allowed interval → no hit

	the hit point is R(t), and the plane normal is constant (N)
*/
bool	hit_plane(t_hittable object, const t_ray r, t_interval ray_t,
			t_hit_record *rec)
{
	t_plane	p;
	double	denom;
	double	t;

	p = object.shape.plane;
	denom = vec3_dot(p.normal, r.direction);
	if (fabs(denom) < 1e-8)
		return (false);
	t = vec3_dot(vec3_sub(p.base, r.origin), p.normal) / denom;
	if (!interval_surrounds(ray_t, t))
		return (false);
	rec->t = t;
	rec->p = at(r, t);
	rec->normal = p.normal;
	rec->color = object.color;
	return (true);
}

t_hittable	create_plane(t_point3 base, t_color3 color, t_vec3 normal)
{
	t_hittable	obj;
	t_plane		plane;

	plane.base = base;
	plane.normal = normal;
	obj.type = OBJ_PLANE;
	obj.shape.plane = plane;
	obj.color = color;
	obj.hit = hit_plane;
	return (obj);
}

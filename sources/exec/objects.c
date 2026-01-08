/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   objects.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/18 12:56:23 by makurek        #+#    #+#                */
/*   Updated: 2026/01/08 16:18:42 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	For each ray we must find:
		P = the coordinates of the intersection point for ray/shape.
		t = the distance from the closest shape.
		n = the surface normal.
	
	For P:
		We solve the equation P(t) = O + tD
	For t:
		Each shape has an equation that makes us able to determin
		if a given ray intersects the shape and where.
		Spheres:	(abs(P - C))^2 = R^2
		Cylinder:	(abs(P−(P⋅N)N-C))^2 = R^2
		Plane:		(P - P0) * N = 0
		Then we replace P by its equation and solve.

 */
bool	hit(t_hittable *object, const t_ray r,
		t_interval ray_t, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	bool			hit_anything;
	double			closest_so_far;
	t_object		shape;
	size_t			i;

	hit_anything = false;
	closest_so_far = ray_t.max;
	i = 0;
	while (object[i].type != OBJ_NULL)
	{
		shape = object[i].shape;
		if (object[i].hit(object[i], r, ray_t, &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			ray_t.max = closest_so_far;
			*rec = temp_rec;
		}
		i++;
	}
	return (hit_anything);
}

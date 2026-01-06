/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   sphere.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/05 17:17:28 by makurek        #+#    #+#                */
/*   Updated: 2026/01/06 17:49:18 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	helper for the hit_sphere function.
*/
static double	compute_root(double h, double a, double c, t_interval ray_t)
{
	double	root;
	double	sqrtd;
	double	discriminant;

	discriminant = h * h - a * c;
	if (discriminant < 0)
		return (false);
	sqrtd = sqrt(discriminant);
	root = (h - sqrtd) / a;
	if (!interval_surrounds(ray_t, root))
		root = (h + sqrtd) / a;
	return (root);
}

/*
    calculates if a ray intersects a sphere

    a sphere centered at C with radius r satisfies:
        (P − C)⋅(P − C) = r²

    a ray is:
        R(t) = O + t·d

    substitute R(t) into the sphere equation and expand:
        (O + t·d − C)⋅(O + t·d − C) = r²

    this becomes a quadratic in t:
        a = d⋅d
        b = −2 d⋅(C − O)
        c = (C − O)⋅(C − O) − r²

    discriminant = b² − 4ac determines number of intersections:
        >0 two hits, =0 one hit, <0 no hit

    solve for t and check if it lies within the allowed interval
*/
bool	hit_sphere(t_hittable object, const t_ray r, t_interval ray_t,
						t_hit_record *rec)
{
	t_vec3		oc;
	double		a;
	double		h;
	double		c;
	t_sphere	sphere;

	sphere = object.shape.sphere;
	oc = vec3_sub(sphere.center, r.origin);
	a = vec3_dot(r.direction, r.direction);
	h = vec3_dot(r.direction, oc);
	c = vec3_length_squared(oc) - sphere.radius * sphere.radius;
	rec->t = compute_root(h, a, c, ray_t);
	if (!interval_surrounds(ray_t, rec->t))
		return (false);
	rec->p = at(r, rec->t);
	rec->normal = vec3_div(vec3_sub(rec->p, sphere.center), sphere.radius);
	rec->color = object.color;
	return (true);
}

t_hittable	create_sphere(t_point3 center, t_color3 color, double radius)
{
	t_hittable	obj;
	t_sphere	sphere;

	sphere.center = center;
	sphere.radius = radius;
	obj.type = OBJ_SPHERE;
	obj.shape.sphere = sphere;
	obj.color = color;
	obj.hit = hit_sphere;
	return (obj);
}

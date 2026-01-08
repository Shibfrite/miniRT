/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   cylinder.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/06 17:39:32 by makurek        #+#    #+#                */
/*   Updated: 2026/01/08 18:40:33 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	project_on_axis(t_vec3 v, t_vec3 axis)
{
	return vec3_scale(axis, vec3_dot(v, axis));
}

static bool	hit_cylinder_side(t_cylinder cy, const t_ray r,
				t_interval ray_t, t_hit_record *rec)
{
	t_vec3	oc;
	t_vec3	d_perp;
	t_vec3	oc_perp;
	double	t_hit;
	double	y;
	t_vec3	cp;
	t_vec3	radial;

	oc = vec3_sub(r.origin, cy.center);
	d_perp = vec3_sub(r.direction, project_on_axis(r.direction, cy.normal));
	oc_perp = vec3_sub(oc, project_on_axis(oc, cy.normal));
	t_hit = compute_root(-0.5 * (2.0 * vec3_dot(d_perp, oc_perp)),
			vec3_dot(d_perp, d_perp),
			vec3_dot(oc_perp, oc_perp) - cy.radius * cy.radius, ray_t);
	if (!interval_contains(ray_t, t_hit))
		return (false);
	rec->p = at(r, t_hit);
	y = vec3_dot(vec3_sub(rec->p, cy.center), cy.normal);
	if (y < 0.0 || y > cy.height)
		return (false);
	rec->t = t_hit;
	cp = vec3_sub(rec->p, cy.center);
	radial = vec3_sub(cp, project_on_axis(cp, cy.normal));
	rec->normal = vec3_unit(radial);
	return (true);
}

static bool	hit_cylinder_cap(t_cylinder cy, const t_ray r,
				t_interval ray_t, t_hit_record *rec)
{
	double		denom;
	double		t;
	t_point3	p;
	t_vec3		diff;

	denom = vec3_dot(r.direction, cy.normal);
	if (fabs(denom) < 1e-12)
		return (false);
	t = vec3_dot(vec3_sub(cy.center, r.origin), cy.normal) / denom;
	if (!interval_contains(ray_t, t))
		return (false);
	p = at(r, t);
	diff = vec3_sub(p, cy.center);
	if (vec3_length_squared(diff) > cy.radius * cy.radius)
		return (false);
	rec->t = t;
	rec->p = p;
	rec->normal = cy.normal;
	return (true);
}

bool	hit_cylinder(t_hittable object, const t_ray r,
					 t_interval ray_t, t_hit_record *rec)
{
	t_cylinder		cy;
	t_hit_record	tmp_rec;
	bool			hit_any;
	double			closest;

	cy = object.shape.cylinder;
	hit_any = false;
	closest = ray_t.max;
	if (hit_cylinder_side(cy, r, ray_t, &tmp_rec) && tmp_rec.t < closest)
	{
		hit_any = true;
		closest = tmp_rec.t;
		*rec = tmp_rec;
	}
	if (hit_cylinder_cap(cy, r, ray_t, &tmp_rec)
		&& tmp_rec.t < closest)
	{
		tmp_rec.normal = vec3_neg(tmp_rec.normal);
		hit_any = true;
		closest = tmp_rec.t;
		*rec = tmp_rec;
	}
	cy.center = vec3_add(cy.center, vec3_scale(cy.normal, cy.height));
	if (hit_cylinder_cap(cy, r, ray_t, &tmp_rec)
		&& tmp_rec.t < closest)
	{
		hit_any = true;
		closest = tmp_rec.t;
		*rec = tmp_rec;
	}
	if (hit_any)
		rec->color = object.color;
	return (hit_any);
}

t_hittable	create_cylinder(t_point3 center, t_color3 color, double radius,
				double height, t_vec3 normal)
{
	t_hittable	obj;
	t_cylinder	cylinder;

	cylinder.center = center;
	cylinder.radius = radius;
	cylinder.height = height;
	cylinder.normal = normal;
	obj.type = OBJ_CYLINDER;
	obj.shape.cylinder = cylinder;
	obj.color = color;
	obj.hit = hit_cylinder;
	return (obj);
}

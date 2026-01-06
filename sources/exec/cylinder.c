/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   cylinder.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/06 17:39:32 by makurek        #+#    #+#                */
/*   Updated: 2026/01/06 18:07:22 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool  hit_cylinder_side(t_cylinder cy, const t_ray r,
                               t_interval ray_t, t_hit_record *rec)
{
    t_vec3  oc = vec3_sub(r.origin, cy.center);
    t_vec3  n = cy.normal;
    t_vec3  d = r.direction;

    t_vec3  d_perp = vec3_sub(d, vec3_scale(n, vec3_dot(d, n)));
    t_vec3  oc_perp = vec3_sub(oc, vec3_scale(n, vec3_dot(oc, n)));

    double  a = vec3_dot(d_perp, d_perp);
    double  b = 2.0 * vec3_dot(d_perp, oc_perp);
    double  c = vec3_dot(oc_perp, oc_perp) - cy.radius * cy.radius;

    double  disc = b * b - 4.0 * a * c;
    if (disc < 0.0 || fabs(a) < 1e-12)
        return false;

    double  sqrt_disc = sqrt(disc);
    double  t0 = (-b - sqrt_disc) / (2.0 * a);
    double  t1 = (-b + sqrt_disc) / (2.0 * a);
    double  t_hit = ray_t.max;

    if (interval_contains(ray_t, t0))
        t_hit = t0;
    if (interval_contains(ray_t, t1) && t1 < t_hit)
        t_hit = t1;
    if (!interval_contains(ray_t, t_hit))
        return false;

    t_point3 p = at(r, t_hit);
    double   y = vec3_dot(vec3_sub(p, cy.center), n);
    if (y < 0.0 || y > cy.height)
        return false;

    rec->t = t_hit;
    rec->p = p;

    t_vec3  cp = vec3_sub(p, cy.center);
    t_vec3  radial = vec3_sub(cp, vec3_scale(n, vec3_dot(cp, n)));
    rec->normal = vec3_unit(radial);
    return true;
}

static bool  hit_cylinder_cap(t_point3 center, t_vec3 normal, double radius,
                              t_cylinder cy, const t_ray r,
                              t_interval ray_t, t_hit_record *rec,
                              bool top_cap)
{
    (void)cy;
    double denom = vec3_dot(r.direction, normal);
    if (fabs(denom) < 1e-12)
        return false;

    double t = vec3_dot(vec3_sub(center, r.origin), normal) / denom;
    if (!interval_contains(ray_t, t))
        return false;

    t_point3 p = at(r, t);
    t_vec3   diff = vec3_sub(p, center);
    if (vec3_length_squared(diff) > radius * radius)
        return false;

    rec->t = t;
    rec->p = p;
    rec->normal = top_cap ? normal : vec3_neg(normal);
    return true;
}

bool    hit_cylinder(t_hittable object, const t_ray r,
                     t_interval ray_t, t_hit_record *rec)
{
    t_cylinder cy = object.shape.cylinder;
    t_hit_record tmp_rec;
    bool        hit_any = false;
    double      closest = ray_t.max;

    // side
    if (hit_cylinder_side(cy, r, ray_t, &tmp_rec) && tmp_rec.t < closest)
    {
        hit_any = true;
        closest = tmp_rec.t;
        *rec = tmp_rec;
    }

    // bottom cap (center at cy.center, normal = cy.normal)
    if (hit_cylinder_cap(cy.center, cy.normal, cy.radius,
                         cy, r, ray_t, &tmp_rec, false)
        && tmp_rec.t < closest)
    {
        hit_any = true;
        closest = tmp_rec.t;
        *rec = tmp_rec;
    }

    // top cap (center at cy.center + n * height, normal = cy.normal)
    t_point3 top_center = vec3_add(cy.center, vec3_scale(cy.normal, cy.height));
    if (hit_cylinder_cap(top_center, cy.normal, cy.radius,
                         cy, r, ray_t, &tmp_rec, true)
        && tmp_rec.t < closest)
    {
        hit_any = true;
        closest = tmp_rec.t;
        *rec = tmp_rec;
    }

    if (hit_any)
        rec->color = object.color;
    return hit_any;
}


t_hittable	create_cylinder(t_point3 center, t_color3 color, double radius, double height, t_vec3 normal)
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

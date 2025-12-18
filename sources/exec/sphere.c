#include "minirt.h"

/*
	calculates if a ray is touching a sphere given it's center and radius

	the calculation is done as follows:

	we use the formula that determins if a point is within a sphere on center.
		x^2+y^2+z^2 = r^2
	we replace the values so that any center could do.
	we simplify by using dot product, develop the variables.
	This makes t the new value we have to solve for.
	We factorise C-Q:
	We make the equation = 0 to get a quadratic equation.
	using the quadratic formula and rearranging the terms we get
	3 terms to solve for
		a = d⋅d
		b = −2d⋅(C−Q)
		c = (C−Q)⋅(C−Q)−r2
	We can simplify using -2h instead of b.
	we solve for the discriminant.
	If the solution is positive we have 2 points.
	if zero 1 point.
	if negative 0 points.
		discriminant = b^2 - 4ac
	then we solve the equation and check if the point is within bounds.
*/
bool	hit_sphere(const t_point3 center, double radius,
						const t_ray r, double tmin, double tmax,
						t_hit_record *rec)
{
	t_vec3	oc;
	double	a;
	double	h;
	double	c;
	double	sqrtd;
	double	root;
	double	discriminant;

	oc = vec3_sub(center, r.origin);
	a = vec3_dot(r.direction, r.direction);
	h = vec3_dot(r.direction, oc);
	c = vec3_length_squared(oc) - radius * radius;
	discriminant = h * h - a * c;
	if (discriminant < 0)
		return (false);
	sqrtd = sqrt(discriminant);
	root = (h - sqrtd) / a;
	if (root <= tmin || root >= tmax)
	{
		root = (h + sqrtd) / a;
		if (root <= tmin || root >= tmax)
			return (false);
	}
	rec->t = root;
	rec->p = at(r, rec->t);
	rec->normal = vec3_div(vec3_sub(rec->p, center), radius);
	return (true);
}

t_hittable	create_sphere(t_point3 center, double radius)
{
	t_hittable	obj;
	t_sphere	sphere;

	sphere.center = center;
	sphere.radius = radius;
	obj.type = OBJ_SPHERE;
	obj.shape.sphere = sphere;
	obj.hit = hit_sphere;
	return (obj);
}

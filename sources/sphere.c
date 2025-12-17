#include "minirt.h"

/*
	calculates if a ray is touching a sphere given it's center and radius

	the calculation is done as follows:

	supposing the center of the sphere is at 0,0,0:
		x^2+y^2+z^2 = r^2

	now for any C center:
		(Cx−x)^2+(Cy−y)^2+(Cz−z)^2=r^2

	using the definition of the dot product:
		(C−P)⋅(C−P)=r^2

	We then replace P by P(t) and develop given that P(t) = Q + td:
		(C−Q+td)⋅(C−Q+td)=r^2
	This makes t the new value we have to solve for.

	We factorise C-Q:
		t^2d⋅d − ^2td ⋅ (C−Q)+(C−Q) ⋅ (C−Q)=r^2

	We move the r^2:
		t^2d⋅d − 2td ⋅ (C−Q)+(C−Q) ⋅ (C−Q)-r^2 = 0

	This is a quadratic equation, hence by using the quadratic formula and rearranging the terms we get:
		a = d⋅d
		b = −2d⋅(C−Q)
		c = (C−Q)⋅(C−Q)−r2

	Then we solve for the discriminant.
	If the solution is positive we have 2 points.
	if zero 1 point.
	if negative 0 points.
		discriminant = b^2 - 4ac

	Somehow if we solve the quadratic it give us
	the exact point at which the ray intersects the sphere.
	This confuses me.

	Note:
		We can simplify using -2h instead of b.
*/
bool hit_sphere(const t_point3 center, double radius,
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

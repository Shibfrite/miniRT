/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   colors.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/11 12:19:39 by makurek        #+#    #+#                */
/*   Updated: 2025/12/16 13:35:06 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

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
static double	hit_sphere(const t_point3 center, double radius, const t_ray r)
{
	t_vec3	oc;
	double	a;
	double	h;
	double	c;
	double	discriminant;

	oc = vec3_sub(center, r.origin);
	a = vec3_dot(r.direction, r.direction);
	h = vec3_dot(r.direction, oc);
	c = vec3_length_squared(oc) - radius * radius;
	discriminant = h * h - a * c;
    if (discriminant < 0)
        return (-1.0);
    else
        return ((h - sqrt(discriminant)) / a);
}

/*
	calculate the color of a single ray.

	the calculation is done as follows:

			unit_direction = unit_vector(r.direction());
			a = 0.5*(unit_direction.y() + 1.0);
			return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
*/
static t_color3	ray_color(const t_ray r)
{
	t_vec3	unit_direction;
	double	a;
	t_vec3	white;
	t_vec3	blue;
	t_vec3	term1;
	t_vec3	term2;

    double t = hit_sphere(vec3_init(0,0,-1), 0.5, r);
    if (t > 0.0) {
        t_vec3 N = vec3_unit(vec3_sub(at(r,t), vec3_init(0,0,-1)));
        return (t_color3){0.5*(N.e[0]+1), 0.5*(N.e[1]+1), 0.5*(N.e[2]+1)};
    }
	unit_direction = vec3_unit(r.direction);
	a = 0.5 * (unit_direction.e[1] + 1.0);
	white = vec3_init(1.0, 1.0, 1.0);
	blue = vec3_init(0.5, 0.7, 1.0);
	term1 = vec3_scale(white, 1.0 - a);
	term2 = vec3_scale(blue, a);
	return (vec3_add(term1, term2));
}

/*
	calculates the color of a single pixel.

	Each pixel is defined as a ray.
	We first calculate the data of each ray.
	Meaning it's starting position (pixel_center),
	And it's direction (ray_direction).
	Then we call ray_color to actually compute the color
	We normalise it by using the scale 0-255 instead of 0-1.
	We bitshift for the format requirement.
*/
int	compute_pixel_color(int x, int y, t_camera camera)
{
	t_point3	pixel_center;
	t_vec3		ray_direction;
	t_vec3		res;
	t_vec3		res1;
	t_color3	color;
	t_ray		ray;

	res = vec3_scale(camera.pixel_length[WIDTH], x);
	res1 = vec3_scale(camera.pixel_length[HEIGHT], y);
	res = vec3_add(res, res1);
	pixel_center = vec3_add(res, camera.first_pixel_location);
	ray_direction = vec3_sub(pixel_center, camera.camera_center);
	ray = ray_init(camera.camera_center, ray_direction);
	color = ray_color(ray);
	return (((unsigned)(255.999 * color.e[0]) << 16) |
		((unsigned)(255.999 * color.e[1]) << 8) |
		(unsigned)(255.999 * color.e[2]));
}

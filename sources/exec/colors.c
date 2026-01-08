/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   colors.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/11 12:19:39 by makurek        #+#    #+#                */
/*   Updated: 2026/01/08 15:08:56 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_point_light {
    t_point3 pos;
    t_color3 intensity; /* can be >1 */
} t_point_light;

t_color3 shade_point_light(t_point3 p, t_vec3 normal,
                           t_point_light L, t_hittable *objects)
{
    t_vec3 toL = vec3_sub(L.pos, p);
    double dist2 = vec3_length_squared(toL);
    t_vec3 dir = vec3_unit(toL);

    t_ray shadow = ray_init(p, dir);
    t_hit_record tmp;
    if (hit(objects, shadow, interval_init(0.001, sqrt(dist2)-0.001), &tmp))
        return vec3_init(0,0,0);

    double nDotL = vec3_dot(normal, dir);
    if (nDotL < 0)
        return vec3_init(0,0,0);

    return vec3_scale(L.intensity, nDotL / dist2);
}


/*
	calculate the color of a single ray.

	the calculation is done as follows:

			unit_direction = unit_vector(r.direction());
			a = 0.5*(unit_direction.y() + 1.0);
			return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
*/
static t_color3 ray_color(const t_ray r, t_hittable *objects, int depth)
{
    t_hit_record rec;

    if (depth <= 0)
        return vec3_init(0,0,0);

    if (!hit(objects, r, interval_init(0.001, INFINITY), &rec))
        return vec3_init(0,0,0); /* no background */

    /* ----- POINT LIGHT ----- */
    t_point_light L = { vec3_init(5,5,5), vec3_init(4,4,4) };
	t_color3 direct = vec3_mul(rec.color,
                           shade_point_light(rec.p, rec.normal, L, objects));

    /* ----- ORIGINAL DIFFUSE BOUNCE ----- */
    t_vec3 bounce_dir = vec3_add(rec.normal, random_unit_vector());
    t_color3 bounced = vec3_mul(
        ray_color(ray_init(rec.p, bounce_dir), objects, depth - 1),
        rec.color
    );

    return vec3_add(direct, bounced);
}

t_vec3	sample_square(void)
{
	return (vec3_init(random_double() - 0.5, random_double() - 0.5, 0.0));
}

t_ray	get_ray(t_camera camera, int x, int y)
{
	t_vec3	offset;
	t_vec3	pixel_sample;
	t_vec3	ray_direction;

	offset = sample_square();
	pixel_sample = vec3_add(
			vec3_add(camera.first_pixel_location,
				vec3_scale(camera.pixel_length[WIDTH],
					(double)x + offset.e[0])),
			vec3_scale(camera.pixel_length[HEIGHT], (double)y + offset.e[1]));
	ray_direction = vec3_sub(pixel_sample, camera.camera_center);
	return (ray_init(camera.camera_center, ray_direction));
}

static double	linear_to_gamma(double linear_component)
{
	if (linear_component > 0.0)
		return (sqrt(linear_component));
	return (0.0);
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
int compute_pixel_color(int x, int y, t_camera camera, t_hittable *objects)
{
    t_interval      intensity;
    t_color3        color;
    unsigned int    normalised_color[3];
    int             sample;

    sample = 0;
    color = vec3_init(0, 0, 0);
    while (sample++ < SAMPLES_PER_PIXEL)
        color = vec3_add(color, ray_color(get_ray(camera, x, y),
                    objects, MAX_DEPTH));
    vec3_div_inplace(&color, SAMPLES_PER_PIXEL);
    intensity = interval_init(0.000, 0.999);
    normalised_color[0] = 256 * linear_to_gamma(
            interval_clamp(intensity, color.e[0]));
    normalised_color[1] = 256 * linear_to_gamma(
            interval_clamp(intensity, color.e[1]));
    normalised_color[2] = 256 * linear_to_gamma(
            interval_clamp(intensity, color.e[2]));
    return ((normalised_color[0] << 16) | (normalised_color[1] << 8)
        | normalised_color[2]);
}


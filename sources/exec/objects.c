/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   objects.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/18 12:56:23 by makurek        #+#    #+#                */
/*   Updated: 2025/12/18 17:29:30 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//we might simplify by removing tmin/tmax
//and using litteral values if they're constants
//that'd solve the norm issue
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
		if (object[i].hit(shape.sphere.center, shape.sphere.radius,
				r, ray_t, &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
		i++;
	}
	return (hit_anything);
}

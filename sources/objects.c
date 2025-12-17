#include "minirt.h"

//we might simplify by removing tmin/tmax by litteral values if they're constants
bool	hit(t_hittable *object, const t_ray r, double tmin, double tmax, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	bool			hit_anything;
	double			closest_so_far;
	t_object		shape;
	size_t			i;

	hit_anything = false;
	closest_so_far = tmax;
	i = 0;
	while (object[i].type != OBJ_NULL)
	{
		shape = object[i].shape;
		if (object[i].hit(shape.sphere.center, shape.sphere.radius, r, tmin, closest_so_far, &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
		i++;
	}
	return (hit_anything);
}

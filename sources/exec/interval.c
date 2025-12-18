#include "minirt.h"

t_interval	interval_init(double min, double max)
{
	t_interval	interval;

	interval.min = min;
	interval.max = max;
	return (interval);
}

double	interval_size(t_interval t)
{
	return (t.max - t.min);
}

bool	interval_contains(t_interval t, double x)
{
	return (t.min <= x && x <= t.max);
}

bool	interval_surrounds(t_interval t, double x)
{
	return (t.min < x && x < t.max);
}

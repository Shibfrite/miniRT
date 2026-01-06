/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   interval.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/05 18:10:05 by makurek        #+#    #+#                */
/*   Updated: 2026/01/05 18:10:06 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

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

double	interval_clamp(t_interval t, double x)
{
	if (x < t.min)
		return (t.min);
	if (x > t.max)
		return (t.max);
	return (x);
}

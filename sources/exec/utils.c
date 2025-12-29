/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   utils.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/29 17:32:23 by makurek        #+#    #+#                */
/*   Updated: 2025/12/29 17:32:24 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>

double	degrees_to_radians(double d)
{
	return (d * M_PI / 180.0);
}

double	random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

double	random_double_range(double min, double max)
{
	return (min + (max - min) * random_double());
}

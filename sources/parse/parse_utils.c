/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                       :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2026/01/14 14:13:21 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_color3	normalise_light(t_color3 color, double brightness)
{
	t_color3	res;

	brightness *= LIGHT_INTENSITY_FACTOR;
	res = vec3_div(color, 255.0);
	res = vec3_scale(res, brightness);
	if (res.e[0] < 0.0)
		res.e[0] = 0.0;
	if (res.e[1] < 0.0)
		res.e[1] = 0.0;
	if (res.e[2] < 0.0)
		res.e[2] = 0.0;
	return (res);
}

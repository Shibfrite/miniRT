/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2026/01/13 22:04:25 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_color3	normalise_light(t_color3 color, double brightness)
{
	t_color3	res;

	res = vec3_div(color, 255.0);
	res = vec3_scale(res, brightness);
	if (res.e[0] < 0.0)
		res.e[0] = 0.0;
	if (res.e[1] < 0.0)
		res.e[1] = 0.0;
	if (res.e[2] < 0.0)
		res.e[2] = 0.0;
	if (res.e[0] > 1.0)
		res.e[0] = 1.0;
	if (res.e[1] > 1.0)
		res.e[1] = 1.0;
	if (res.e[2] > 1.0)
		res.e[2] = 1.0;
	return (res);
}

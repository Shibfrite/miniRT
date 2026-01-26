/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:04:44 by anpayot           #+#    #+#             */
/*   Updated: 2026/01/26 14:25:26 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_error(const char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd((char *)msg, 2);
	return (FAILURE);
}

const char	*skip_spaces(const char *str)
{
	while (*str && is_space(*str))
		str++;
	return (str);
}

/* color expected in 0..255 range per channel */
/* clamp to [0,1] just in case */
t_color3	normalise_light(t_color3 color, double brightness)
{
	t_color3	res;

	(void)brightness;
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

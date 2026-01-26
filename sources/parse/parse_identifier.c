/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:26:20 by anpayot           #+#    #+#             */
/*   Updated: 2026/01/26 14:26:20 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_identifier(t_scene *scene, char **tokens)
{
	if (ft_strcmp(tokens[0], "A") == 0)
		return (parse_ambient(scene, tokens));
	if (ft_strcmp(tokens[0], "C") == 0)
		return (parse_camera(scene, tokens));
	if (ft_strcmp(tokens[0], "L") == 0)
		return (parse_light(scene, tokens));
	if (ft_strcmp(tokens[0], "sp") == 0)
		return (parse_sphere(scene, tokens));
	if (ft_strcmp(tokens[0], "pl") == 0)
		return (parse_plane(scene, tokens));
	if (ft_strcmp(tokens[0], "cy") == 0)
		return (parse_cylinder(scene, tokens));
	return (parse_error(ERR_UNKNOWN_ID));
}

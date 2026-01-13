/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 by anpayot           #+#    #+#             */
/*   Updated: 2026/01/13 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_ambient(t_scene *scene, char **tokens)
{
	double	ratio;

	if (scene->ambient.is_set)
		return (parse_error(ERR_DUPLICATE_AMBIENT));
	if (!tokens[1] || !tokens[2] || tokens[3])
		return (parse_error(ERR_INVALID_TOKEN_COUNT));
	if (parse_double_token(tokens[1], &ratio) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (ratio < 0.0 || ratio > 1.0)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_color(tokens[2], &scene->ambient.color) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	scene->ambient.color = normalise_light(scene->ambient.color, ratio);
	scene->ambient.ratio = ratio;
	scene->ambient.is_set = true;
	return (SUCCESS);
}

int	parse_camera(t_scene *scene, char **tokens)
{
	int	fov_int;

	if (scene->cam_spec.is_set)
		return (parse_error(ERR_DUPLICATE_CAMERA));
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (parse_error(ERR_INVALID_TOKEN_COUNT));
	if (parse_vec3(tokens[1], &scene->cam_spec.position) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_normalized_vec3(tokens[2], &scene->cam_spec.orientation)
		== FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_int_range(tokens[3], 0, 180, &fov_int) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	scene->cam_spec.fov = (double)fov_int;
	scene->cam_spec.is_set = true;
	return (SUCCESS);
}

int	parse_light(t_scene *scene, char **tokens)
{
	t_light	light;
	double	brightness;

	if (scene->light_count >= MAX_LIGHTS)
		return (parse_error(ERR_TOO_MANY_LIGHTS));
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (parse_error(ERR_INVALID_TOKEN_COUNT));
	if (parse_vec3(tokens[1], &light.pos) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_double_token(tokens[2], &brightness) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (brightness < 0.0 || brightness > 1.0)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_color(tokens[3], &light.color) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	light.color = normalise_light(light.color, brightness);
	scene->lights[scene->light_count] = light;
	scene->light_count++;
	return (SUCCESS);
}

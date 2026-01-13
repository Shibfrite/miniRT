/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 by anpayot           #+#    #+#             */
/*   Updated: 2026/01/13 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_sphere(t_scene *scene, char **tokens)
{
	t_point3	center;
	t_color3	color;
	double		diameter;

	if (scene->object_count >= MAX_OBJECTS)
		return (parse_error(ERR_TOO_MANY_OBJECTS));
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (parse_error(ERR_INVALID_TOKEN_COUNT));
	if (parse_vec3(tokens[1], &center) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_double_token(tokens[2], &diameter) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (diameter <= 0.0)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_color(tokens[3], &color) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	color = vec3_div(color, 255.0);
	scene->objects[scene->object_count] = create_sphere(center, color,
			diameter / 2.0);
	scene->object_count++;
	return (SUCCESS);
}

int	parse_plane(t_scene *scene, char **tokens)
{
	t_point3	point;
	t_vec3		normal;
	t_color3	color;

	if (scene->object_count >= MAX_OBJECTS)
		return (parse_error(ERR_TOO_MANY_OBJECTS));
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (parse_error(ERR_INVALID_TOKEN_COUNT));
	if (parse_vec3(tokens[1], &point) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_normalized_vec3(tokens[2], &normal) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_color(tokens[3], &color) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	color = vec3_div(color, 255.0);
	scene->objects[scene->object_count] = create_plane(point, color, normal);
	scene->object_count++;
	return (SUCCESS);
}

int	parse_cylinder(t_scene *scene, char **tokens)
{
	t_point3	center;
	t_vec3		axis;
	t_color3	color;
	double		dims[2];

	if (scene->object_count >= MAX_OBJECTS)
		return (parse_error(ERR_TOO_MANY_OBJECTS));
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5]
		|| tokens[6])
		return (parse_error(ERR_INVALID_TOKEN_COUNT));
	if (parse_vec3(tokens[1], &center) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_normalized_vec3(tokens[2], &axis) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_double_token(tokens[3], &dims[0]) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_double_token(tokens[4], &dims[1]) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (dims[0] <= 0.0 || dims[1] <= 0.0)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_color(tokens[5], &color) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	color = vec3_div(color, 255.0);
	dims[0] = dims[0] / 2.0;
	scene->objects[scene->object_count] = create_cylinder(center, color, dims,
			axis);
	scene->object_count++;
	return (SUCCESS);
}

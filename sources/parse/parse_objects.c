/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:06:03 by anpayot           #+#    #+#             */
/*   Updated: 2026/01/26 14:21:18 by anpayot          ###   ########.fr       */
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

static int	parse_cylinder_values(char **tokens, t_cylinder_parse *data)
{
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5]
		|| tokens[6])
		return (parse_error(ERR_INVALID_TOKEN_COUNT));
	if (parse_vec3(tokens[1], &data->center) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_normalized_vec3(tokens[2], &data->axis) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_double_token(tokens[3], &data->dims[0]) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_double_token(tokens[4], &data->dims[1]) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (data->dims[0] <= 0.0 || data->dims[1] <= 0.0)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_color(tokens[5], &data->color) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	data->color = vec3_div(data->color, 255.0);
	data->dims[0] = data->dims[0] / 2.0;
	return (SUCCESS);
}

int	parse_cylinder(t_scene *scene, char **tokens)
{
	t_cylinder_parse	data;

	if (scene->object_count >= MAX_OBJECTS)
		return (parse_error(ERR_TOO_MANY_OBJECTS));
	if (parse_cylinder_values(tokens, &data) == FAILURE)
		return (FAILURE);
	scene->objects[scene->object_count] = create_cylinder(data.center,
			data.color, data.dims, data.axis);
	scene->object_count++;
	return (SUCCESS);
}

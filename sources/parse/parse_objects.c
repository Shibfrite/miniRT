/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:03:34 by anpayot           #+#    #+#             */
/*   Updated: 2026/01/13 22:03:37 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

struct s_cyl_data
{
	t_point3	center;
	t_vec3		axis;
	double		dims[2];
	t_color3	color;
};

static int	load_cylinder(char **tokens, struct s_cyl_data *cyl)
{
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4]
		|| !tokens[5] || tokens[6])
		return (parse_error(ERR_INVALID_TOKEN_COUNT));
	if (parse_vec3(tokens[1], &cyl->center) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_normalized_vec3(tokens[2], &cyl->axis) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_double_token(tokens[3], &cyl->dims[0]) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_double_token(tokens[4], &cyl->dims[1]) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	if (cyl->dims[0] <= 0.0 || cyl->dims[1] <= 0.0)
		return (parse_error(ERR_INVALID_VALUE));
	if (parse_color(tokens[5], &cyl->color) == FAILURE)
		return (parse_error(ERR_INVALID_VALUE));
	return (SUCCESS);
}

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
	struct s_cyl_data	cyl;

	if (scene->object_count >= MAX_OBJECTS)
		return (parse_error(ERR_TOO_MANY_OBJECTS));
	if (load_cylinder(tokens, &cyl) == FAILURE)
		return (FAILURE);
	cyl.color = vec3_div(cyl.color, 255.0);
	cyl.dims[0] = cyl.dims[0] / 2.0;
	scene->objects[scene->object_count] = create_cylinder(cyl.center,
			cyl.color, cyl.dims, cyl.axis);
	scene->object_count++;
	return (SUCCESS);
}

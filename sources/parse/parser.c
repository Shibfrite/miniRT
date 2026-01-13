/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 10:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/12/24 18:50:47 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	parse_line(t_scene *scene, char *line);
static int	validate_scene(t_scene *scene);

/*
	Check if filename ends with .rt
*/
int	check_file_extension(const char *filename)
{
	int	len;

	if (!filename)
		return (FAILURE);
	len = ft_strlen(filename);
	if (len < 4)
		return (FAILURE);
	if (ft_strcmp(filename + len - 3, ".rt") != 0)
		return (FAILURE);
	return (SUCCESS);
}

/*
	Main parsing entry point
*/
int	parse_scene(t_scene *scene, const char *filename)
{
	int		fd;
	char	*line;
	int		status;
	int		err;

	if (!scene)
		return (FAILURE);
	if (check_file_extension(filename) == FAILURE)
		return (parse_error(ERR_EXTENSION));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (parse_error(ERR_OPEN));
	err = 0;
	line = get_next_line(fd, &err);
	while (line && !err)
	{
		if (!is_empty_or_comment(line))
		{
			status = parse_line(scene, line);
			if (status == FAILURE)
				return (free(line), close(fd), FAILURE);
		}
		free(line);
		line = get_next_line(fd, &err);
	}
	close(fd);
	if (err)
		return (parse_error(ERR_READ));
	return (validate_scene(scene));
}

/*
	Print error message to stderr and return FAILURE
*/
int	parse_error(const char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd((char *)msg, 2);
	return (FAILURE);
}

/*
	Check if line is empty or a comment (starts with #)
*/
int	is_empty_or_comment(const char *line)
{
	char	*ptr;

	ptr = (char *)skip_spaces(line);
	if (*ptr == '\0' || *ptr == '\n' || *ptr == '#')
		return (1);
	return (0);
}

static int	parse_line(t_scene *scene, char *line)
{
	char	**tokens;
	int		status;

	tokens = split_whitespace(line);
	if (!tokens || !tokens[0])
		return (free_tokens(tokens), FAILURE);
	if (ft_strcmp(tokens[0], "A") == 0)
		status = parse_ambient(scene, tokens);
	else if (ft_strcmp(tokens[0], "C") == 0)
		status = parse_camera(scene, tokens);
	else if (ft_strcmp(tokens[0], "L") == 0)
		status = parse_light(scene, tokens);
	else if (ft_strcmp(tokens[0], "sp") == 0)
		status = parse_sphere(scene, tokens);
	else if (ft_strcmp(tokens[0], "pl") == 0)
		status = parse_plane(scene, tokens);
	else if (ft_strcmp(tokens[0], "cy") == 0)
		status = parse_cylinder(scene, tokens);
	else
		status = parse_error(ERR_UNKNOWN_ID);
	free_tokens(tokens);
	return (status);
}

static int	validate_scene(t_scene *scene)
{
	if (!scene->cam_spec.is_set)
		return (parse_error(ERR_MISSING_CAMERA));
	if (!scene->ambient.is_set)
		return (parse_error(ERR_MISSING_AMBIENT));
	if (scene->light_count == 0)
		return (parse_error(ERR_MISSING_LIGHT));
	if (scene->object_count == 0)
		return (parse_error(ERR_MISSING_OBJECT));
	scene->objects[scene->object_count].type = OBJ_NULL;
	return (SUCCESS);
}

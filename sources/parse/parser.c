/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 10:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2026/01/26 14:25:26 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	validate_scene(t_scene *scene);
static int	parse_scene_loop(t_scene *scene, int fd);

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
	int		status;

	if (!scene)
		return (FAILURE);
	if (check_file_extension(filename) == FAILURE)
		return (parse_error(ERR_EXTENSION));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (parse_error(ERR_OPEN));
	status = parse_scene_loop(scene, fd);
	close(fd);
	if (status == FAILURE)
		return (FAILURE);
	return (validate_scene(scene));
}

/*
	Print error message to stderr and return FAILURE
*/
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

static int	parse_scene_loop(t_scene *scene, int fd)
{
	char	*line;
	int		err;
	int		status;

	err = 0;
	line = get_next_line(fd, &err);
	while (line && !err)
	{
		if (!is_empty_or_comment(line))
		{
			status = parse_line(scene, line);
			if (status == FAILURE)
				return (free(line), FAILURE);
		}
		free(line);
		line = get_next_line(fd, &err);
	}
	if (err)
		return (parse_error(ERR_READ));
	return (SUCCESS);
}

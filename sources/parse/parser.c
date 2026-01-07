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

/*
	Check if filename ends with .rt
*/
int	check_file_extension(char *filename)
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
	TODO: implement full parsing
*/
int	parse_scene(t_scene *scene, char *filename)
{
	int	fd;

	if (!scene)
		return (FAILURE);
	if (check_file_extension(filename) == FAILURE)
	{
		ft_putendl_fd(ERR_EXTENSION, 2);
		return (FAILURE);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd(ERR_OPEN, 2);
		return (FAILURE);
	}
	(void)scene;
	// TODO: read file with get_next_line
	// TODO: parse each line (A, C, L, sp, pl, cy)
	// TODO: fill scene structure
	close(fd);
	return (SUCCESS);
}

/*
	Print error message to stderr and return FAILURE
*/
int	parse_error(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
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

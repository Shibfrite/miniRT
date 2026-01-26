/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2026/01/26 14:25:43 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	fill_tokens(const char *line, char **tokens, int count);

static int	count_tokens(const char *line)
{
	int	count;

	count = 0;
	line = skip_spaces(line);
	while (*line)
	{
		count++;
		while (*line && !is_space(*line))
			line++;
		line = skip_spaces(line);
	}
	return (count);
}

char	**split_whitespace(const char *line)
{
	int		count;
	char	**tokens;

	if (!line)
		return (NULL);
	count = count_tokens(line);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	if (fill_tokens(line, tokens, count) == FAILURE)
		return (free_tokens(tokens), NULL);
	return (tokens);
}

void	free_tokens(char **tokens)
{
	int	idx;

	if (!tokens)
		return ;
	idx = 0;
	while (tokens[idx])
	{
		free(tokens[idx]);
		tokens[idx] = NULL;
		idx++;
	}
	free(tokens);
}

static int	fill_tokens(const char *line, char **tokens, int count)
{
	int			i;
	const char	*end;

	i = 0;
	line = skip_spaces(line);
	while (i < count)
	{
		end = line;
		while (*end && !is_space(*end))
			end++;
		tokens[i] = ft_substr(line, 0, end - line);
		if (!tokens[i])
			return (FAILURE);
		line = skip_spaces(end);
		i++;
	}
	tokens[count] = NULL;
	return (SUCCESS);
}

int	parse_line(t_scene *scene, char *line)
{
	char	**tokens;
	int		status;

	tokens = split_whitespace(line);
	if (!tokens || !tokens[0])
		return (free_tokens(tokens), FAILURE);
	status = parse_identifier(scene, tokens);
	free_tokens(tokens);
	return (status);
}

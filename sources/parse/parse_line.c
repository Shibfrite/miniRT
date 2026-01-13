/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/12/24 18:50:47 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

const char	*skip_spaces(const char *str)
{
	while (*str && is_space(*str))
		str++;
	return (str);
}

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

static char	*dup_token(const char *start, const char *end)
{
	return (ft_substr(start, 0, end - start));
}

static const char	*find_token_end(const char *str)
{
	while (*str && !is_space(*str))
		str++;
	return (str);
}

char	**split_whitespace(const char *line)
{
	int		count;
	char	**tokens;
	int		i;

	if (!line)
		return (NULL);
	count = count_tokens(line);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	line = skip_spaces(line);
	while (i < count)
	{
		tokens[i] = dup_token(line, find_token_end(line));
		if (!tokens[i])
			return (free_tokens(tokens), NULL);
		line = find_token_end(line);
		line = skip_spaces(line);
		i++;
	}
	tokens[count] = NULL;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2026/01/13 22:02:25 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

const char	*skip_spaces(const char *str)
{
	while (*str && is_space(*str))
		str++;
	return (str);
}

static int	count_tokens(const char *line)
{
	int			count;
	const char	*next;

	count = 0;
	line = skip_spaces(line);
	while (*line)
	{
		count++;
		next = line;
		while (*next && !is_space(*next))
			next++;
		line = skip_spaces(next);
	}
	return (count);
}

static int	fill_tokens(char **tokens, int count, const char *line)
{
	int			idx;
	const char	*start;

	idx = 0;
	line = skip_spaces(line);
	while (idx < count)
	{
		start = line;
		while (*line && !is_space(*line))
			line++;
		tokens[idx] = ft_substr(start, 0, line - start);
		if (!tokens[idx])
			return (free_tokens(tokens), FAILURE);
		line = skip_spaces(line);
		idx++;
	}
	return (SUCCESS);
}

char	**split_whitespace(const char *line)
{
	int	count;
	char	**tokens;

	if (!line)
		return (NULL);
	count = count_tokens(line);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	if (fill_tokens(tokens, count, line) == FAILURE)
		return (NULL);
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

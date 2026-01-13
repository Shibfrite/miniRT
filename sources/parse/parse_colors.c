/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/12/24 18:50:47 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	copy_component(const char *s, int start, int end, int *out)
{
	char	*chunk;
	int		status;

	chunk = ft_substr(s, start, end - start);
	if (!chunk)
		return (FAILURE);
	status = parse_int_range(chunk, 0, 255, out);
	free(chunk);
	return (status);
}

static int	parse_components(const char *s, int c[3])
{
	int	idx;
	int	start;
	int	count;

	idx = 0;
	start = 0;
	count = 0;
	while (s[idx] && count < 3)
	{
		if (s[idx] == ',')
		{
			if (copy_component(s, start, idx, &c[count]) == FAILURE)
				return (FAILURE);
			count++;
			start = idx + 1;
		}
		idx++;
	}
	if (count == 2 && copy_component(s, start, idx, &c[2]) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}

int	parse_color(const char *s, t_color3 *out)
{
	int	c[3];

	if (!s || !out)
		return (FAILURE);
	if (parse_components(s, c) == FAILURE)
		return (FAILURE);
	*out = vec3_init((double)c[0], (double)c[1], (double)c[2]);
	return (SUCCESS);
}

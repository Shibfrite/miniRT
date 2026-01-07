/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/12/24 18:50:47 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	copy_component(const char *s, int start, int end, double *out)
{
	char	*chunk;
	int		status;

	chunk = ft_substr(s, start, end - start);
	if (!chunk)
		return (FAILURE);
	status = parse_double_token(chunk, out);
	free(chunk);
	return (status);
}

static int	parse_components(const char *s, double v[3])
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
			if (copy_component(s, start, idx, &v[count]) == FAILURE)
				return (FAILURE);
			count++;
			start = idx + 1;
		}
		idx++;
	}
	if (count == 2 && copy_component(s, start, idx, &v[2]) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}

int	parse_vec3(const char *s, t_vec3 *out)
{
	double	v[3];

	if (!s || !out)
		return (FAILURE);
	if (parse_components(s, v) == FAILURE)
		return (FAILURE);
	*out = vec3_init(v[0], v[1], v[2]);
	return (SUCCESS);
}

static int	within_unit_range(const t_vec3 v)
{
	return (v.e[0] >= -1.0 && v.e[0] <= 1.0
		&& v.e[1] >= -1.0 && v.e[1] <= 1.0
		&& v.e[2] >= -1.0 && v.e[2] <= 1.0);
}

int	parse_normalized_vec3(const char *s, t_vec3 *out)
{
	double	len;

	if (parse_vec3(s, out) == FAILURE)
		return (FAILURE);
	if (!within_unit_range(*out))
		return (FAILURE);
	len = vec3_length(*out);
	if (fabs(len - 1.0) > 1e-6)
		return (FAILURE);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2026/01/26 14:21:18 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	consume_int(const char *s, long *value, int *idx)
{
	int	digit_count;

	digit_count = 0;
	while (ft_isdigit(s[*idx]))
	{
		*value = *value * 10 + (s[*idx] - '0');
		*idx += 1;
		digit_count++;
	}
	return (digit_count);
}

static void	init_double_parse(t_double_parse *p)
{
	p->idx = 0;
	p->sign = 1;
	p->int_part = 0;
	p->frac_part = 0.0;
	p->divisor = 10.0;
	p->digits = 0;
}

static void	consume_fraction(const char *s, t_double_parse *p)
{
	while (ft_isdigit(s[p->idx]))
	{
		p->frac_part += (s[p->idx] - '0') / p->divisor;
		p->divisor *= 10.0;
		p->digits += 1;
		p->idx += 1;
	}
}

int	parse_double_token(const char *s, double *out)
{
	t_double_parse	p;

	if (!s || !out)
		return (FAILURE);
	init_double_parse(&p);
	if (s[p.idx] == '+' || s[p.idx] == '-')
	{
		if (s[p.idx] == '-')
			p.sign = -1;
		p.idx += 1;
	}
	p.digits += consume_int(s, &p.int_part, &p.idx);
	if (s[p.idx] == '.')
	{
		p.idx++;
		consume_fraction(s, &p);
	}
	if (p.digits == 0 || s[p.idx] != '\0')
		return (FAILURE);
	*out = p.sign * (p.int_part + p.frac_part);
	return (SUCCESS);
}

int	parse_int_range(const char *s, int min, int max, int *out)
{
	int		idx;
	int		sign;
	long	value;
	int		digits;

	if (!s || !out)
		return (FAILURE);
	idx = 0;
	sign = 1;
	value = 0;
	digits = 0;
	if (s[idx] == '+' || s[idx] == '-')
	{
		if (s[idx] == '-')
			sign = -1;
		idx++;
	}
	digits += consume_int(s, &value, &idx);
	if (digits == 0 || s[idx] != '\0')
		return (FAILURE);
	value *= sign;
	if (value < min || value > max)
		return (FAILURE);
	*out = (int)value;
	return (SUCCESS);
}

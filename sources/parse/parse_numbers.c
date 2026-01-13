/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/12/24 18:50:47 by anpayot          ###   ########.fr       */
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

static void	init_double_vars(int *idx, int *sign, long *int_part,
				double *frac_part)
{
	*idx = 0;
	*sign = 1;
	*int_part = 0;
	*frac_part = 0.0;
}

static void	apply_sign(const char *s, int *idx, int *sign)
{
	if (s[*idx] == '+' || s[*idx] == '-')
	{
		if (s[*idx] == '-')
			*sign = -1;
		*idx += 1;
	}
}

static void	consume_fraction(const char *s, int *idx, double *frac_part,
						 double *divisor, int *digits)
{
	while (ft_isdigit(s[*idx]))
	{
		*frac_part += (s[*idx] - '0') / *divisor;
		*divisor *= 10.0;
		*digits += 1;
		*idx += 1;
	}
}

int	parse_double_token(const char *s, double *out)
{
	int		idx;
	int		sign;
	long	int_part;
	double	frac_part;
	double	divisor;
	int		digits;

	if (!s || !out)
		return (FAILURE);
	divisor = 10.0;
	digits = 0;
	init_double_vars(&idx, &sign, &int_part, &frac_part);
	apply_sign(s, &idx, &sign);
	digits += consume_int(s, &int_part, &idx);
	if (s[idx] == '.')
	{
		idx++;
		consume_fraction(s, &idx, &frac_part, &divisor, &digits);
	}
	if (digits == 0 || s[idx] != '\0')
		return (FAILURE);
	*out = sign * (int_part + frac_part);
	return (SUCCESS);
}

int	parse_int_range(const char *s, int min, int max, int *out)
{
	int	idx;
	int	sign;
	long	value;
	int	digits;

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_numbers.c                                     :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2026/01/14 13:46:29 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

struct s_dbl_ctx
{
	int		idx;
	int		sign;
	long	int_part;
	double	frac_part;
	double	divisor;
	int		digits;
};

static int	consume_int(const char *s, long *value, int *idx)
{
	int		digit_count;

	digit_count = 0;
	while (ft_isdigit(s[*idx]))
	{
		*value = *value * 10 + (s[*idx] - '0');
		*idx += 1;
		digit_count++;
	}
	return (digit_count);
}

static void	init_double_vars(struct s_dbl_ctx *ctx)
{
	ctx->idx = 0;
	ctx->sign = 1;
	ctx->int_part = 0;
	ctx->frac_part = 0.0;
	ctx->divisor = 10.0;
	ctx->digits = 0;
}

static int	consume_fraction(const char *s, struct s_dbl_ctx *ctx)
{
	int		added;

	added = 0;
	while (ft_isdigit(s[ctx->idx]))
	{
		ctx->frac_part += (s[ctx->idx] - '0') / ctx->divisor;
		ctx->divisor *= 10.0;
		added += 1;
		ctx->idx += 1;
	}
	return (added);
}

int	parse_double_token(const char *s, double *out)
{
	struct s_dbl_ctx	ctx;

	if (!s || !out)
		return (FAILURE);
	init_double_vars(&ctx);
	if (s[ctx.idx] == '+' || s[ctx.idx] == '-')
	{
		if (s[ctx.idx] == '-')
			ctx.sign = -1;
		ctx.idx++;
	}
	ctx.digits += consume_int(s, &ctx.int_part, &ctx.idx);
	if (s[ctx.idx] == '.')
	{
		ctx.idx++;
		ctx.digits += consume_fraction(s, &ctx);
	}
	if (ctx.digits == 0 || s[ctx.idx] != '\0')
		return (FAILURE);
	*out = ctx.sign * (ctx.int_part + ctx.frac_part);
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

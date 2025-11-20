/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbussien <jbussien@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 00:41:07 by jbussien          #+#    #+#             */
/*   Updated: 2024/12/19 00:41:07 by jbussien         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_write_char(const char c)
{
	if (write(1, &c, 1) != 1)
		return (-1);
	return (1);
}

static void	ft_write_word(char *str, int *out)
{
	while (*str)
	{
		ft_check_error(ft_write_char(*str), out);
		if (*out < 0)
			return ;
		str++;
	}
}

void	ft_write_str(char *str, int *out)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		ft_write_word("(null)", out);
		return ;
	}
	while (str[i])
	{
		ft_check_error(ft_write_char(str[i]), out);
		if (*out < 0)
			return ;
		i++;
	}
}

void	ft_write_integer(int n, int	*out)
{
	if (n == 0)
	{
		ft_check_error(ft_write_char('0'), out);
		return ;
	}
	if (n == -2147483648)
	{
		ft_write_str("-2147483648", out);
		return ;
	}
	if (n < 0)
	{
		ft_check_error(ft_write_char('-'), out);
		if (*out < 0)
			return ;
		n *= -1;
	}
	if (n > 9)
		ft_write_integer(n / 10, out);
	if (*out < 0)
		return ;
	ft_check_error(ft_write_char((n % 10) + 48), out);
}

void	ft_write_uint(uint32_t n, int *out)
{
	if (n == 0)
	{
		ft_check_error(ft_write_char('0'), out);
		return ;
	}
	if (n > 9)
		ft_write_uint(n / 10, out);
	if (*out < 0)
		return ;
	ft_check_error(ft_write_char((n % 10) + 48), out);
}

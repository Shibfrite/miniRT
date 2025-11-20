/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbussien <jbussien@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 00:41:19 by jbussien          #+#    #+#             */
/*   Updated: 2024/12/19 00:41:19 by jbussien         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_check_error(int res, int *out)
{
	if (res < 0)
		*out = -1;
	if (*out >= 0)
		*out += res;
}

void	ft_write_hex_low(uint32_t nbr, int *out)
{
	if (nbr >= 16)
		ft_write_hex_low(nbr / 16, out);
	if (*out < 0)
		return ;
	if ((nbr % 16) > 9)
		ft_check_error(ft_write_char((nbr % 16) - 10 + 97), out);
	else
		ft_check_error(ft_write_char((nbr % 16) + 48), out);
}

void	ft_write_hex_high(uint32_t nbr, int *out)
{
	if (nbr >= 16)
		ft_write_hex_high(nbr / 16, out);
	if (*out < 0)
		return ;
	if ((nbr % 16) > 9)
		ft_check_error(ft_write_char((nbr % 16) - 10 + 65), out);
	else
		ft_check_error(ft_write_char((nbr % 16) + 48), out);
}

void	ft_write_hex_ptr(uintptr_t nbr, int *out)
{
	if (nbr >= 16)
		ft_write_hex_ptr(nbr / 16, out);
	if (*out < 0)
		return ;
	if ((nbr % 16) > 9)
		ft_check_error(ft_write_char((nbr % 16) - 10 + 97), out);
	else
		ft_check_error(ft_write_char((nbr % 16) + 48), out);
}

void	ft_write_ptr(void *ptr, int *out)
{
	uintptr_t	nbr;

	ft_write_str("0x", out);
	if (*out < 0)
		return ;
	nbr = (uintptr_t)ptr;
	ft_write_hex_ptr(nbr, out);
}

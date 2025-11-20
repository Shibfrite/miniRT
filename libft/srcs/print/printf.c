/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbussien <jbussien@student.42lausanne.ch>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 00:40:54 by jbussien          #+#    #+#             */
/*   Updated: 2024/12/19 00:41:00 by jbussien         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_parse_and_print(const char *str, va_list	*args, int *out);
static void	ft_dispatch(const char c, va_list *args, int *out);
static int	ft_check_symbol(char c);

// faire un parseur pour extraire les types 
// faire un dispatcheur pour aiguiller les types
int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		out;

	out = 0;
	va_start(args, str);
	ft_parse_and_print(str, &args, &out);
	va_end(args);
	return (out);
}

static int	ft_check_symbol(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd'
		|| c == 'i' || c == 'u' || c == 'x'
		|| c == 'X' || c == '%' )
	{
		return (1);
	}
	return (0);
}

static void	ft_dispatch(const char c, va_list *args, int *out)
{
	if (c == 'c')
		ft_check_error(ft_write_char(va_arg(*args, int)), out);
	else if (c == 's')
		ft_write_str(va_arg(*args, char *), out);
	else if (c == 'p')
		ft_write_ptr(va_arg(*args, void *), out);
	else if (c == 'd' || c == 'i')
		ft_write_integer(va_arg(*args, int), out);
	else if (c == 'u')
		ft_write_uint(va_arg(*args, uint32_t), out);
	else if (c == 'x')
		ft_write_hex_low(va_arg(*args, uint32_t), out);
	else if (c == 'X')
		ft_write_hex_high(va_arg(*args, uint32_t), out);
	else if (c == '%')
		ft_check_error(ft_write_char('%'), out);
}

static void	ft_parse_and_print(const char *str, va_list	*args, int *out)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (ft_check_symbol(str[i + 1]))
				ft_dispatch(str[++i], args, out);
		}
		else
			ft_check_error(ft_write_char(str[i]), out);
		if (*out < 0)
			return ;
		i++;
	}
}
	/*
	printf("arg1 char 		%c\n", (char)va_arg(args, int));
	printf("arg2 integer		%d\n", va_arg(args, int));
	printf("arg3 uint		%llu\n", va_arg(args, uint64_t));
	printf("arg4 str		%s\n", va_arg(args, char*));
	printf("arg5 ptr adr		%p\n", va_arg(args, char*));
	*/

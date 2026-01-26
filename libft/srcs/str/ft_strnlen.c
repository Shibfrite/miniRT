/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strnlen.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/26 15:49:56 by makurek        #+#    #+#                */
/*   Updated: 2026/01/26 15:49:58 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	const char	*start = s;

	start = s;
	while (maxlen-- && *s)
		s++;
	return (s - start);
}

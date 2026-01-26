/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strndup.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/26 15:49:48 by makurek        #+#    #+#                */
/*   Updated: 2026/01/26 15:49:50 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	len;
	char	*dup;

	len = ft_strnlen(src, n);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, src, len);
	dup[len] = '\0';
	return (dup);
}

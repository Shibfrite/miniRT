/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strncpy.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/26 15:49:36 by makurek        #+#    #+#                */
/*   Updated: 2026/01/26 15:49:37 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

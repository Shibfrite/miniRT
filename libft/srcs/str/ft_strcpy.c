/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strcpy.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/26 15:49:18 by makurek        #+#    #+#                */
/*   Updated: 2026/01/26 15:49:19 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*ptr;

	if (!dest || !src)
		return (NULL);
	ptr = dest;
	while (*src)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}

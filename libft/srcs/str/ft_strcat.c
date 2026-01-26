/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strcat.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/26 15:49:01 by makurek        #+#    #+#                */
/*   Updated: 2026/01/26 15:49:03 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	char	*ptr;

	if (!dest || !src)
		return (NULL);
	ptr = dest;
	while (*ptr)
		ptr++;
	while (*src)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}

#include "libft.h"

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	const char	*start = s;

	start = s;
	while (maxlen-- && *s)
		s++;
	return (s - start);
}

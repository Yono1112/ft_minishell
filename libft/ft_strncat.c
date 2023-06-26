#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t len)
{
	char	*s;

	s = dst;
	while (*s)
		s++;
	while (len > 0 && *src)
	{
		*s = *src;
		s++;
		src++;
		len--;
	}
	*s = '\0';
	return (dst);
}

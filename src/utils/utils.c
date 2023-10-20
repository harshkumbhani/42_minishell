
#include "minishell.h"

char	*ft_strndup(const char *str, size_t n)
{
	char	*dup;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(str);
	if (n < len)
		len = n;
	dup = ft_calloc(1, len + 1);
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

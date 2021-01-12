#include <stdlib.h>
#include <unistd.h>

int     lentochar(char *s, char c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return -1;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return i;
}

void	ft_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
#include "../../minishell.h"

int		nb_tabs(char **s)
{
	int		nb_tabs;

	nb_tabs = 0;
	while (s[nb_tabs])
		nb_tabs++;
	return (nb_tabs);
}

char *ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

int ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}
 
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*oct1;
	unsigned char	*oct2;

	if (dst == src || n == 0)
		return (dst);
	oct1 = (unsigned char*)dst;
	oct2 = (unsigned char*)src;
	while (n--)
		*oct1++ = *oct2++;
	return (dst);
}

char *ft_strstr(char *str, char *to_find)
{
	int i;
	int j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (str + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void				ft_bzero(void *b, size_t n)
{
	unsigned char	*dest;
	size_t			i;

	dest = b;
	i = 0;
	while (i++ < n)
		*dest++ = 0;
}

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (!(mem = malloc(size)))
		return (NULL);
	ft_bzero(mem, size);
	return (mem);
}

 

#include <string.h>

char	**ft_copy_tab(char **env)
{
	int		i;
	int		size;
	char	**envp;

	size = 0;
	i = -1;
	size = nb_tabs(env);
	envp = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		envp[i] = strdup(env[i]); // A REMPLACER ! pourquoi ne repere pas mon ft_strdup ????
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

void ft_putchar(int c)
{
	write(1, &c, 1);
}

void ft_putstr(char *s)
{
	int	i;

	i = 0;
	while(s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

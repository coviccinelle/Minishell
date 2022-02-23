#include "../../minishell.h"

void    ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!(s) || fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
}

void    ft_putendl_fd(char *s, int fd)
{
	if (!(s) || fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

int	ft_puterror_fd(char *error, char *s, char *error2)
{
	ft_putstr_fd(error, 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(error2, 2);
	ft_putchar_fd('\n', 2);
	return (EXIT_FAILURE);
}


int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}


//leaks
/*
char	*ft_strdup(char *s1)
{
	char	*str;
	int		i;
	int		size;

	size = 0;
	while (s1[size])
	{
		size++;
	}
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
*/

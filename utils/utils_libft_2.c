#include "../minishell.h"

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

void	ft_puterror_fd(char *error, char *s, char *error2)
{
	ft_putstr_fd(error, 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(error2, 2);
	ft_putchar_fd('\n', 2);
}

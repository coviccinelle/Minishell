#include "../../../minishell.h"

void	exec_exit(int ac, char **av)
{
	if (ac > 3)
	{
		if (!is_digit(av[1][0])) // a rechecker si chaque element de la string ou juste le premier
		{
			ft_putstr_fd("exit\n", 1);
			ft_puterror_fd("minishell: exit: ", av[1], ":numeric argument required");
		}
		else
			ft_puterror_fd("exit: ", "too many arguments", NULL);
	}
}


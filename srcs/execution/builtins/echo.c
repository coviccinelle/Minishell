#include "../../../minishell.h"

int	is_option_n(char *av)
{
	int	i;

	i = 0;
	if (!av)
		return (0);
	if (av[0] != '-')
		return (0);
	while (av[++i])
		if (av[i] != 'n')
			return (0);
	return (1);
}

int	echo(int ac, char **av, int option_n)
{
	int j;
	if (option_n == 1) 
		j = 2;
	else if (option_n == 0) 
		j = 1;
	if (ac > 1)
	{
		while (is_option_n(av[j]))
			j++;
		while (av[j])
		{
			ft_putstr_fd(av[j], 1);
			if ((j + 1) != ac) // ajouter plutot ac - 1 si bug apres parsing thao. sinon fonctionen tres bien on its own (mets un espace supp dans mon exec mais cest normal car &av[1])
				ft_putchar_fd(' ', 1);
			j++;
		}
	}
	if (option_n == 0)
		ft_putchar_fd('\n', 1);
	return (EXIT_SUCCESS);
}

int	exec_echo(int ac, char **av)
{
	int	n;

	n = is_option_n(av[1]);
	echo(ac, av, n);
	return (EXIT_SUCCESS);
}

/*
int	main(int ac, char **av)
{
	exec_echo(ac, av); 
}
*/

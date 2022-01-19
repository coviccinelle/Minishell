#include "../minishell.h"

int	exec_echo(int ac, char **av, int option_n) //data->option_n
{
	int j;
	if (option_n == 1) 
		j = 2; // (car av[0] est "echo" et av[1] est "-n")
	else if (option_n == 0) 
		j = 1; //(car av[0] est "echo")
	if (ac > 1) // si ac == 1 && -n, return success. et n \n et return
	{
		while (av[j])
		{
			ft_putstr_fd(av[j], 1);
			if ((j + 1) != ac) // si bug surement ici; tenter j ou ac + 1. nb d'args à enregistrer dans struct
				ft_putchar_fd(' ', 1);
			j++;
		}
	}
	if (option_n == 0)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}
/*
int	main(int ac, char **av)
{
	exec_echo(ac, av, 0); // echo 
	exec_echo(ac, av, 1); // echo -n
}
*/

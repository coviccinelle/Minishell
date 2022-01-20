#include "../../minishell.h"
/*
// option n a checker ceci est le seul parsing necessaire sauf erreur
int	is_option_n(char **av)
{
	int	option_n;
	char *str;

	option_n = 0;
	str = NULL;
	if (ft_strlen(av[1]) == ft_strlen(« -n »))
	{
		if (ft_strcmp(«-n», av[1]) == 0)
			option_n = 1;
	}
	else if (ft_strlen(av[1]) > ft_strlen(«-n»))
	{
		str = ft_memset(&av[1][3], 'n', ft_strlen(av[1]) - 3);
		if ((ft_strncmp(«-n», av[1], ft_strlen(«-n») == 0) && (ft_strncmp(&av[1][3], str) == 0))
			option_n = 1;
	}
	return (option_n);
}
*/
#include <string.h>
int	is_option_n(char **av)
{
	int	option_n;
	char *str;

	option_n = 0;
	str = NULL;
	char	*n;
	n = "-n";
	if (strlen(av[1]) == strlen(n))
	{
		if (strcmp(n, av[1]) == 0)
			option_n = 1;
	}
	else if (strlen(av[1]) > strlen(n))
	{
		printf("taille de av[1] == %ld et taille de n = %ld\n", strlen(av[1]), strlen(n));
		str = memset(&av[1][2], 'n', strlen(av[1]) - strlen(n));
		printf("str = %s\n", str);
		if (strncmp(n, av[1], strlen(n + 1) == 0))
		{

			printf("je passe ici\n"); // NE PASSE PAS PAR LA. DE PLUS IL FAUT METTRE FONCTIONS DE LA LIFT ICI JAI TRICHE
			if (strncmp(&av[1][2], str, strlen(&av[1][2]) == 0))
				option_n = 1;
		}

	}
	return (option_n);
}

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

int	main(int ac, char **av)
{
	printf("is option_n = %d\n", is_option_n(av));
//	exec_echo(ac, av, 0); // echo 
	exec_echo(ac, av, 1); // echo -n
}


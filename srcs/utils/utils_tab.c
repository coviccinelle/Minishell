#include "../../minishell.h"

//char	**ft_copy_tab(char **env);

// int	ft_strcmp(char *s, char *t)
// {
// 	while (*s && (*s == *t))
// 	{
// 		s++;
// 		t++;
// 	}
// 	return (*s - *t);
// }

void	print_export(char **tab)
{
	int	j;

	j = -1;
	while (tab[++j])
		printf("declare -x %s\n", tab[j]);
}

#include <string.h> //a enlever

int	print_env(int ac, char **av, char **env) // plus print tab mais print env plutot vu que je viens dajouter la condition strchr
{
	int	j;
	int exit_status;

	j = -1;
	if (ac >= 2)
	{
		ft_puterror_fd("env: ", av[1], ": No such file or directory");
		exit_status = 127;
		return (exit_status);

	}	
	while (env[++j])
	{
		if (strchr(env[j], '=')) // a remplacer par ft_strchr
			printf("%s\n", env[j]);
	}
	return (EXIT_SUCCESS);
}

void swap(char **s1, char **s2)
{
  char *tmp;
  
  tmp = *s1;
  *s1= *s2;
  *s2 = tmp;
}  



int	ft_alphabetical_order_tab(char **env)
{
	char	**copy;
	//char	*tmp;
	int		i;
	int		j;

	copy = ft_copy_tab(env);
	i = 0;
	j = 0;
	while (copy[i])
	{
		j = i + 1;
		while (copy[j])
		{
			if (ft_strcmp(copy[i], copy[j]) > 0)
				swap(&copy[i], &copy[j]);
			j++;
		}
		i++;
	}
	print_export(copy);
	free_tab(&copy);
	return (0);
}


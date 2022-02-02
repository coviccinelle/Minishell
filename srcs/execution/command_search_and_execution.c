#include "../../minishell.h"


/*

// 1/ fonction ft_strcmp list of shell builtins.
int		is_builtin(char *builtin)
{
	if (!(ft_strcmp(builtin, "cd")))
		return (1);
	if (!(ft_strcmp(builtin, "echo"))
		return (1);
	if (!(ft_strcmp(builtin, "env"))
		return (1);
	if (!(ft_strcmp(builtin, "export"))
		return (1);
	if (!(ft_strcmp(builtin, "exit"))
		return (1);
	if (!(ft_strcmp(builtin, "pwd"))
		return (1);
	if (!(ft_strcmp(builtin, "unset"))
		return (1);
	return (0);
}
// 2/ if == 1. exec builtin.else print error msg command not found
int exec_builtin(char *builtin, char **av)
{
		int exit_status;

		exit_status =  EXIT_SUCCESS; 
		if (!(ft_strcmp(builtin, "cd")))
			exit_status = exec_cd(av);
		if (!(ft_strcmp(builtin, "echo"))
			exit_status = exec_echo(av);
		if (!(ft_strcmp(builtin, "env"))
			exit_status = exec_env(av);
		if (!(ft_strcmp(builtin, "export"))
			exit_status = exec_export(av); // + &export list. de 4/
		if (!(ft_strcmp(builtin, "exit"))
			exit_status = exec_exit(av);
		if (!(ft_strcmp(builtin, "pwd"))
			exit_status = exec_pwd(av);
		if (!(ft_strcmp(builtin, "unset"))
			exit_status = exec_unset(av); // + &export list. de 4/
		if (exit_status != 0)
			exit_status = EXIT_FAIL; // If a command is found but is not executable, the return status is 126.
		return (exit_status);
}

//utils

int	ft_strcmp(char *s, char *t)
{
	while (*s && (*s == *t))
	{
		s++;
		t++;
	}
	return (*s - *t);
}
*/

char	*ft_strxjoin(char *s1, char *s2, char *s3)
{
		char *res;
		char	*tmp;

		tmp = ft_strjoin(s1, s2);
		res = ft_strjoin(tmp, s3);
		free(tmp);
		return (res);
}

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


char	**ft_split(char *s, char sep)
{
	char	**tab;
	int		nb_tabs;
	int		i;
	int		j;

	nb_tabs = 0;
	j = -1;
	while (s[++j])
		if (s[j] == sep)
			nb_tabs++;
	tab = malloc(sizeof(char *) * (nb_tabs + 2));
	tab[nb_tabs + 1] = NULL;
	j = 0;
	while (j < nb_tabs + 1)
	{
		i = 0;
		while (s[i] && s[i] != sep)
			i++;
		tab[j++] = ft_strndup(s, i);
		s = &s[i + 1];
	}
	return (tab);
}

char	*find_cmd_path(char *cmd)
{
	char	**path;
	char	*absolute_path;
	int		j;
	struct stat	s;

	j = -1;
	if (!cmd)
		return (NULL);
	path = ft_split(getenv("PATH"), ':'); // mettre a lexterieur car flemme de rajouter env en param // ft_split et ft_getenv
	while (path[++j])
	{
		absolute_path = ft_strxjoin(path[j], "/", cmd);
        	if (stat(absolute_path, &s) == 0)
		{
			free_tab(&path);
			return (absolute_path); // a free pour le dernier ft_strjoin non?
		}
		ft_memdel(&absolute_path);
	}
	free_tab(&path);
	ft_memdel(&absolute_path);
	return (NULL);
}



void	exec_cmd(int ac, char **av, char **env)
{
	char	*path;

	path = find_cmd_path(av[1]); // a remplacer par av[0] apres. je mets c1 pour tester en attendant parsing
//	if (is_builtin(av[0]) //return 0 for success
//		exec_builtin(av[0], av); // all builtin return an exit status of 2 to indicate incorrate usage such as invalid option or missing arguments
//	else
	printf("path trouve = %s\n\n", path);
		execve(path, av, env); // if a command is found but is not executable, the return status is 126
//	else
//		ft_puterror_fd("Minishell:", "command not found", av[0]);// exit status 127. if a command is not foundm the child process to execute it returns a status of 127
}

int	main(int ac, char **av, char **env)
{
/*	char	*final;

	final = ft_strxjoin(av[1], av[2], av[3]);
	printf("%s\n", final);
*/
/*	char *s = find_cmd_path(av[1]);
	printf("%s\n", s);
	if (s != NULL)
		free(s); // A FREE DANS LE MAIN PRINCIPAL !!!!!!
*/
	exec_cmd(ac, av, env);
	return (0);
}


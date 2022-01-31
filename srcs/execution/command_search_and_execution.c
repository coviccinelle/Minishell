#include "../../minishell.h"


void	exec()
{
	char	*path;

	path = find_path(); // cf ma fonction dans env je sais plus si je lavais appelee comme ca
	if (is_builtin) // a retrouver dans mon notion
		exec_builtin; // a retrouver dans mon notion puis tester apres parsing de thao
	else
		execve(path, NULL, env); // sais plus le truc du milieu a rechecker
	else
		ft_puterror_fd(av[0], "command not found", NULL);
}

// file : command_search_and_execution.c
/* All builtins return an exit status of 2 
to indicate incorrect usage, 
generally invalid options or missing arguments.
donc ici exit_fail = 2 et non pas 126 ? quand pour 126 ?)
*/
if (is_builtin(av[0]))
		exit_status = exec_builtin(av[0], av); // If a command is found but is not executable, the return status is 126.
else
{
		printf("Minishell: command not found: %s\n", av[0]);
		exit_status = 127; //If a command is not found, the child process created to execute it returns a status of 127. 
}
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


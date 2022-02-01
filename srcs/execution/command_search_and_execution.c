#include "../../minishell.h"


void	exec_cmd(int ac, char **av, char **env)
{
	char	*path;

	path = find_cmd_path(av[0]); // cf ma fonction dans env (encore a tester)
	if (is_builtin(av[0]) //return 0 for success
		exec_builtin(av[0], av); // all builtin return an exit status of 2 to indicate incorrate usage such as invalid option or missing arguments
	else
		execve(path, av, env); // if a command is found but is not executable, the return status is 126
	else
		ft_puterror_fd("Minishell:", "command not found", av[0]);// exit status 127. if a command is not foundm the child process to execute it returns a status of 127
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


#include "../../minishell.h"
//#include <unistd.h>
#include<sys/wait.h>

// 1/ fonction ft_strcmp list of shell builtins.
int	is_builtin(char *builtin)
{
	if (!(ft_strcmp(builtin, "cd")))
		return (1);
	if (!(ft_strcmp(builtin, "echo")))
		return (1);
	if (!(ft_strcmp(builtin, "env")))
		return (1);
	if (!(ft_strcmp(builtin, "export")))
		return (1);
	if (!(ft_strcmp(builtin, "exit")))
		return (1);
	if (!(ft_strcmp(builtin, "pwd")))
		return (1);
	if (!(ft_strcmp(builtin, "unset")))
		return (1);
	return (0);
}

// 2/ if == 1. exec builtin.else print error msg command not found
int exec_builtin(char *builtin, int ac, char **av, char ***env)
{
		int exit_status;

		exit_status =  EXIT_SUCCESS; 
		if (!(ft_strcmp(builtin, "cd")))
			exec_cd(ac, av, *env);
		//if (!(ft_strncmp(builtin, "echo", ft_strlen("echo"))))
		if (!(ft_strcmp(builtin, "echo")))
			exit_status = exec_echo(ac, av);
		if (!(ft_strcmp(builtin, "env")))
			print_env(*env);
		if (!(ft_strcmp(builtin, "export")))
			exit_status = exec_export(ac, av, env); // + &export list. de 4/
		if (!(ft_strcmp(builtin, "exit")))
			exec_exit(ac, av);
		if (!(ft_strcmp(builtin, "pwd")))
			exit_status = exec_pwd();
		if (!(ft_strcmp(builtin, "unset")))
			exit_status = exec_unset(ac, av, env); // + &export list. de 4/
		if (exit_status != 0)
			exit_status = EXIT_FAILURE; // If a command is found but is not executable, the return status is 126.
		return (exit_status);
}


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

char	*find_cmd_path(char *cmd, char **env)
{
	char	**path;
	char	*absolute_path;
	int		j;
	struct stat	s;
	char	*possible_paths;

	possible_paths = ft_getenv(env, "PATH");
	j = -1;
	if (!cmd)
		return (NULL);
	path = ft_split(possible_paths, ':'); // mettre a lexterieur car flemme de rajouter env en param // ft_getenv
	free(possible_paths);
	while (path[++j])
	{
		absolute_path = ft_strxjoin(path[j], "/", cmd);
	//	printf("absolute_path[%d] = %s\n", j, absolute_path);
		if (stat(absolute_path, &s) == 0)
		{
			free_tab(&path);
	//		printf("last absolute path = %s\n", absolute_path);
			return (absolute_path); // a free pour le dernier ft_strjoin non?
		}
		ft_memdel(&absolute_path);
	}
	free_tab(&path);
	ft_memdel(&absolute_path);
	return (NULL);
}

#include <errno.h>  
#include <string.h>

void safely_exec_bin_cmds(char *path, char **av, char **env, int *exit_status) //le moment venu,  ajouter ***env en param
{
	if (execve(path, av, env) < 0) //le moment venu, remplacer NULL par *env
	{
		perror(path);
		*exit_status = 1; // a remplacer par g_exit ? anyway faire attention car de base je voulais ret tout en meme temps a la fin de exec_cmd mais la jai un exit donc cet exit_status ne sera pas pris en compte
		//si bug dans mes pipes, remettre exit(EXIT_FAILURE);
	}
}

int	exec_cmd(int ac, char **av, char ***env)
{
	char	*path;
	int	relative;
	int 	exit_status;
	(void)ac;

	path = NULL;
	relative = 0;
	exit_status = 0;
	if ((access(av[0], F_OK)) == 0)
	{
		relative = 1;
		path = strdup(av[0]); // remplacer par ft_strdup
	}
	if (relative == 0)
		path = find_cmd_path(av[0], *env);
	if (path == NULL)
	{
		ft_puterror_fd("minishell: ", "command not found: ", av[0]);
		exit_status = 127; // if a command is not found the child process to execute it returns a status of 127
	}
	else if (path != NULL)
		safely_exec_bin_cmds(path, av, *env, &exit_status);
	return (exit_status);
}
/*
int	main(int ac, char **av, char **envp)
{
	//OLD OK
	char **env;

	env = ft_copy_tab(envp);
	pid_t	father;

	father = fork();
	if (father > 0)
	{
		wait(NULL);
		printf("I AM YOUR FATHER\n");
	}
	if (father == 0)
	{
		sleep(3);
		exec_cmd(ac, av, &env);
	}
	free_tab(&env);
//	print_env(env);

	return (0);
}
*/


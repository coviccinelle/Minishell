#include "../../minishell.h"

// 1/ fonction ft_strcmp list of shell builtins.
int		is_builtin(char *builtin)
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
//		if (!(ft_strcmp(builtin, "cd")))
//			exit_status = exec_cd(ac, av);
		if (!(ft_strcmp(builtin, "echo")))
			exit_status = exec_echo(ac, av);
//		if (!(ft_strcmp(builtin, "env")))
//			exit_status = exec_env(ac, av);
		if (!(ft_strcmp(builtin, "export")))
			exit_status = exec_export(ac, av, env); // + &export list. de 4/
//		if (!(ft_strcmp(builtin, "exit")))
//			exit_status = exec_exit(ac, av);
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

	j = -1;
	if (!cmd)
		return (NULL);
	path = ft_split(ft_getenv(env, "PATH"), ':'); // mettre a lexterieur car flemme de rajouter env en param // ft_getenv
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

#include <errno.h>  

void	exec_cmd(int ac, char **av, char ***env)
{
	char	*path;

	path = find_cmd_path(av[1], *env); // a remplacer par av[0] apres. je mets c1 pour tester en attendant parsing
	int	ret;

	ret = 0;
	if (is_builtin(av[1])) //a remplacer par av[0] apres.
		exec_builtin(av[1], ac, &av[1], env); // a remplacer par av[0] et av[1] apres. all builtin return an exit status of 2 to indicate incorrate usage such as invalid option or missing arguments
	else if (path == NULL)
		ft_puterror_fd("minishell: ", "command not found", av[0]);// exit status 127. if a command is not foundm the child process to execute it returns a status of 127
	else if (!is_builtin(av[1]))
		//printf("path trouve = %s\n\n", path);
		ret = execve(path, &av[1], *env); // . a remplacer par av apres en attendant parsing. if a command is found but is not executable, the return status is 126
	if (ret == -1) // en cas de reussite exceve ne revient pas mais en cas dechec renvoie -1 avec le code derreur dans errno
		strerror(errno);
		//perror("");
}

int	main(int ac, char **av, char **envp)
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
	char **env;

	env = ft_copy_tab(envp);
	exec_cmd(ac, av, &env);
	print_env(env);
	return (0);
}

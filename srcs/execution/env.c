#include "../../minishell.h"

//EXEC


//Execute commands but this time without any path. (ls, wc, awk etc...)


//fonction ok. a mettre dans utils_libft_1.c si jamais

char	*ft_strxjoin(char *s1, char *s2, char *s3)
{
		char *res;
		char	*tmp;

		tmp = ft_strjoin(s1, s2);
		res = ft_strjoin(tmp, s3);
		free(tmp);
		return (res);
}


/*
char	*find_cmd_path(char *cmd) // a renommer
{
	char	**path;
	char	*absolute_path;
	int		j;
	struct stat	s;

	j = -1;
	path = ft_split(ft_getenv(env, "PATH"), ':'); // mettre a lexterieur car flemme de rajouter env en param
	while (path[++j])
	{
		absolute_path = ft_strxjoin(path[j], "/", cmd);
		//if (access(asolute_path, F_OK) == 0)
        	if (stat(absolute_path, &s) == 0)
		{
			free_tab(&path);
			return (absolute_path); // a free pour le dernier ft_strjoin non?
		}
		ft_memdel(absolute_path);
	}
	free_tab(&path);
}
*/

int	main(int ac, char **av)
{
	char	*final;

	final = ft_strxjoin(av[1], av[2], av[3]);
	printf("%s\n", final);
	return (0);
}

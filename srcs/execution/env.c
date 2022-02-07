#include "../../minishell.h"

//EXEC
//Execute commands but this time without any path. (ls, wc, awk etc...)


//dernier cas a gerer : pq me segfault quand il ne trouve rien ? sinon ok pour trouver pwd ls etc

//fonction ok. a mettre dans utils_libft_1.c si jamais

/*
char	*ft_strxjoin(char *s1, char *s2, char *s3)
{
		char *res;
		char	*tmp;

		tmp = ft_strjoin(s1, s2);
		res = ft_strjoin(tmp, s3);
		free(tmp);
		return (res);
}
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
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
*/

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

int	main(int ac, char **av)
{
/*	char	*final;

	final = ft_strxjoin(av[1], av[2], av[3]);
	printf("%s\n", final);
*/
	char *s = find_cmd_path(av[1]);
	printf("%s\n", s);
	if (s != NULL)
		free(s); // A FREE DANS LE MAIN PRINCIPAL !!!!!!
	return (0);
}

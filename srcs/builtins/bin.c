#include "../../minishell.h"

//encore à tester

char	*ft_strxjoin(char *s1, char *s2, char *s3)
{
		char *res;
		char	*tmp;

		tmp = ft_strjoin(s1, s2);
		res = ft_strjoin(tmp, s3);
		free(tmp);
		return (res);
}

char	*find_cmd_path(char *cmd) // a renommer
{
	char	**path;
	char	*absolute_path;
	int		j;
    struct stat	s;

	j = -1;
	path = ft_split(getenv("PATH"), ':'); //mon ft_getenv plutot non?
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

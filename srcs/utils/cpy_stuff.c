
#include "../../minishell.h"

char    *ft_strdup(char *s1)
{
        char    *str;
        int             i;
        int             size;

        size = 0;
        while (s1[size])
        {
                size++;
        }
        str = malloc((size + 1) * sizeof(char));
        if (!str)
                return (NULL);
        i = 0;
        while (s1[i])
        {
                str[i] = s1[i];
                i++;
        }
        str[i] = '\0';
        return (str);
}

char	**ft_env_cpy(char **envp)
{
	int		i;
	int		size;
	char	**env;

	size = 0;
	i = 0;
	while (envp[i++])
		size++;
	env = malloc(sizeof(char *) * (size + 1));
	i = -1;
	while (++i < size)
		env[i] = ft_strdup(envp[i]);
	env[i] = NULL;
	return (env);
}

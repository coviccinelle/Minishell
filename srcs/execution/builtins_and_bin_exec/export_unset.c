/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:25:42 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/07 18:38:02 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	env_realloc_and_append_envvar(char ***env, char *envvar)
{
	int		j;
	char	**new_env;
	int		new_size;

	j = 0;
	new_size = nb_tabs(*env) + 2;
	new_env = (char **)malloc(sizeof(char *) * new_size);
	if (!new_env)
		return (-1);
	while ((*env)[j] && j < nb_tabs(*env))
	{
		new_env[j] = ft_strndup((*env)[j], ft_strlen((*env)[j]));
		j++;
	}
	new_env[j] = ft_strndup(envvar, ft_strlen(envvar));
	new_env[j + 1] = NULL;
	free_tab(env);
	*env = new_env;
	return (0);
}

int	comp_env(char *s, char *s1)
{
	int	j;

	j = -1;
	while(s && s1 && s[++j] && s1[j])
	{
		if(s[j] != s1[j])
			return(s[j] - s1[j]);
	}
	if(s1[j] == '\0' && s[j] == '\0')
		return(0);
	if(s1[j] != '\0')
		return((-(s1[j]));
	else
		return(s[j]);

}

char	*find_in_env(char **env, char *name, int *pos)
{
	int	j;
	int	name_len;
	char	*s;
	int	c;

	name_len = ft_strlen(name);
	j = -1;
	if (name == NULL || env == NULL)
	{
		return (NULL);
	}
	while (env[++j] && j < nb_tabs(env))
	{
		s = cpy_trim(env[j], env[j][0], '=');
		//fprintf(stderr, "\n S = %s\n", s);
		if ((c = comp_env(name, s)) == 0)
		{
			*pos = j;
			fprintf(stderr, "\n comparaison de s(%s) et name(%s) =  %d \n", s, name, c);
			if(s)
				free(s);
			return (cpy_trim(env[j], '=', '\0'));
		}
		if(s)
			free(s);
	}
	return (ft_strdup(""));
}

char	*ft_getenv(char **env, char *name)
{
	int	pos;

	pos = 0;
	return (find_in_env(env, name, &pos));
}

int	ft_setenv(char ***env, char *av, char *name, char *value)
{
	int	pos_name;
	int	free_me;

	free_me = 0;
	if (av == NULL)
	{
		free_me = 1;
		av = ft_strxjoin(name, "=", value);
	}
	if (find_in_env(*env, name, &pos_name) != NULL && value != NULL)
		ft_unsetenv(env, name);
	if((find_in_env(*env, name, &pos_name) != NULL && value != NULL) || !(find_in_env(*env, name, &pos_name) != NULL))
		env_realloc_and_append_envvar(env, av);
	if (free_me == 1)
		free(av);
	return (0);
}

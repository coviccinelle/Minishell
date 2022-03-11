/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:25:42 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/11 17:30:01 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	free_new_env(char ***s)
{
	int		i;

	i = 0;
	while ((*s)[i])
	{
		free((*s[i]));
		i++;
	}
	free(*s);
}

int	env_realloc_and_append_envvar(char ***env, char *envvar)
{
	int		j;
	char	**new_env;
	int		new_size;

	j = 0;
	new_size = nb_tabs(*env) + 2;
	new_env = malloc(sizeof(char *) * new_size);
	if (!new_env)
		return (-1);
	while ((*env)[j] && j < nb_tabs(*env))
	{
		new_env[j] = ft_strndup((*env)[j], ft_strlen((*env)[j]));
		j++;
	}
	new_env[j] = ft_strndup(envvar, ft_strlen(envvar));
	new_env[j + 1] = NULL;
	if (*env)
		free_tab_3(*env, nb_tabs(*env));
	*env = new_env;
	return (0);
}

char	**env_realloc_and_append_envvarr(char **env, char *envvar)
{
	int		j;
	char	**new_env;
	int		new_size;

	j = 0;
	new_size = nb_tabs(env) + 2;
	new_env = malloc(sizeof(char *) * new_size);
	if (!new_env)
		return (NULL);
	while ((env)[j] && j < nb_tabs(env))
	{
		new_env[j] = ft_strndup((env)[j], ft_strlen((env)[j]));
		j++;
	}
	new_env[j] = ft_strndup(envvar, ft_strlen(envvar));
	new_env[j + 1] = NULL;
	return (new_env);
}

int	comp_env(char *s, char *s1)
{
	int	j;

	j = -1;
	while (s && s1 && s[++j] && s1[j])
	{
		if (s[j] != s1[j])
			return (s[j] - s1[j]);
	}
	if (s1[j] == '\0' && s[j] == '\0')
		return (0);
	if (s1[j] != '\0')
		return ((-(s1[j])));
	else
		return (s[j]);
}

char	*find_in_env(char **env, char *name, int *pos)
{
	int		j;
	char	*s;
	int		c;

	j = -1;
	if (name == NULL || env == NULL)
		return (NULL);
	while (env[++j] && j < nb_tabs(env))
	{
		s = cpy_trim(env[j], env[j][0], '=');
		c = comp_env(name, s);
		if (c == 0)
		{
			*pos = j;
			if (s)
				free(s);
			return (cpy_trim(env[j], '=', '\0'));
		}
		if (s)
			free(s);
	}
	return (ft_strdup(""));
}

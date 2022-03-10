/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:25:42 by mloubet           #+#    #+#             */
/*   Updated: 2022/03/10 18:32:34 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*ft_getenv(char **env, char *name)
{
	int	pos;

	pos = 0;
	return (find_in_env(env, name, &pos));
}

int	ft_setenv(char ***env, char *av, char *name, char *value)
{
	int		pos_name;
	int		free_me;
	char	*s;

	free_me = 0;
	if (av == NULL)
	{
		free_me = 1;
		av = ft_strxjoin(name, "=", value);
	}
	s = find_in_env(*env, name, &pos_name);
	if (s != NULL && value != NULL)
		ft_unsetenv(env, name);
	if (s != NULL)
		env_realloc_and_append_envvar(env, av);
	if (s)
		free(s);
	if (free_me == 1)
		free(av);
	return (0);
}

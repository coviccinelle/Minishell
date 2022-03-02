
#include "../../minishell.h"

// char	*dollar_sign(int ac, char **av, char **env)
// {
// 	int j;
// 	char	*s;

// 	s = NULL;
// 	j = -1;
// 	while (av[++j])
// 	{
// 		if (av[j][0]  == '$' && av[j][1]  == '?')
// 			get_exit_status(); // comment vu que pas possible var globale?? Ret de fonction a mettre dans notre liste chainee “mini”?
// 		else if (av[j][0]  == '$' && av[j][1] != NULL)
// 			s = ft_getenv(env, av[j]); // rechecker nom final que je lui ai donne et tester le tout
// 		else if (!ft_strcmp(av[j], "~"))
// 			s = ft_getenv(env, "HOME"); // a free
// 	}
// 	return(s);
// }



// int	is_dollar(int c)
// {

// 	if (str[i] && str[i] == '$' && is_alpha(str[i + 1]))
// 		return (1);
// 	else
// 		return (0);
// }

// return => $USER
char	*dolar_name(char *str, int *i, char *line_after, t_cmd *cmd)
{
	if (line_after)
	{
		ft_avs(cmd, line_after);
		line_after = NULL;
	}
	(*i)++;
	while (str[*i] && str[*i] != ' ')
	{
		line_after = ft_add_line_after(line_after, str[*i]);
		(*i)++;
	}
	return (line_after);
}

char	*dolar_2(char *str, int *i, char *line_after, char **envp)
{
	printf("IN DOLAR 2.0\n");
	printf("line_after BEFORE GET_ENV in dolar_2 == should be $USER %s\n", line_after);
	printf("1er ligne de env %s\n", envp[0]);
	//line_after = NULL;

//	line_after = ft_getenv(envp, line_after);
	line_after = ft_getenv(envp, "USER");
	printf("line_after in GET_ENV in dolar_2 == %s\n", line_after);

	printf("IN DOLAR 2.1\n");
	if (str[*i])
	{
		while (str[*i] == ' ')
			(*i)++;
	}
	printf("IN DOLAR 2.2\n");
	printf("line_after in dolar_2 == %s\n", line_after);
	return (line_after);
}

// *** // Dollar sign : go search the value in
// char	*dollar_name(char *str/*, int *i*//*, char *line_after*/)
// {
// 	char	*name;
// 	int i = 0;

// 	name = NULL;
	
// 	//if (str[*i] == '$' && is_alpha[*i + 1])
// 	if (str[i] && str[i] == '$' && is_alpha(str[i + 1]))
// 	{
// 		(i)++;
// 		while (str[i] && is_alpha(str[i] && str[i] != ' '))
// 		{
// 			name = ft_add_line_after(name, str[i]);
// 			(i)++;
// 		}
// 		printf("name = %s\n", name);
// 		return (name);
// 	}
// 	printf("out of boucle\n");
// 	return (NULL);

// }


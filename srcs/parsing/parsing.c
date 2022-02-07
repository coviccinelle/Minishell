/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:43:23 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/07 16:02:22 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/*
int	is_token(char *str, char *token)
{
	char	*res;

	res = strstr(str, token);
	if (res == NULL)
		return (0);
	return (1);
}*/

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned long	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (!n || str1 == str2)
		return (0);
	while (str1[i] && str2[i] && i < (n - 1) && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

// int	ft_strlen(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }


int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	detect_cmd(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(str, "echo", 5))
		{
			printf("ECHO founded\n");
			return (ft_strlen("echo"));
		}
		if (!ft_strncmp(str, "export", 7))
		{
			printf("EXPORT founded\n");
			return (ft_strlen("export"));
		}
		if (!ft_strncmp(str, "env", 4))
		{
			printf("ENV founded\n");
			return (ft_strlen("env"));
		}
		if (!ft_strncmp(str, "exit", 5))
		{
			printf("EXIT founded\n");
			return (ft_strlen("exit"));
		}
		if (!ft_strncmp(str, "cd", 3))
		{
			printf("CD founded\n");
			return (ft_strlen("cd"));
		}
		if (!ft_strncmp(str, "pwd", 4))
		{
			printf("PWD founded\n");
			return (ft_strlen("pwd"));
		}
		if (!ft_strncmp(str, "unset", 6))
		{
			printf("UNSET founded\n");
			return (ft_strlen("unset"));
		}
		i++;
	}
	return (0);
}

// there are 2 choices : put all in la liste chainee or tableau + liste chainee, depends on Marie-Ines
//Step 1: parsing espaces and avs
// step 2: counting (single and doubles) quotes
//  Step 3: tokenizing in liste chainee (2 ways: Balkis (tableau + liste chainee for each cmd) and Eclipse (liste chainee 100%))
int	parsing(t_mini *mini/*, t_cmd *cmd*/)
{
	//int i;
	//char	*buf;
	//char	**str= NULL;
	//(void)cmd;

	//buf = NULL;
	//i = 0;
	while (mini->line)
	{
		if (ft_strchr(mini->line, '|'))
		{
			mini->i = ft_piping(mini->line, mini->cmd); // = t_cmd *cmd
			printf("%d\n", mini->i);
			return  (1);
		}
		else
		{
			printf("There's only one cmd! Simple\n");
			printf("line = %s\n", mini->line);
			if (ft_each_cmd(mini->line, mini->cmd))
				return (1);
			//return (1);
		}
		return (0);
		// // else
		// // {
		// // 	printf("Errr: command not found\n");
		// // //	i++;
		// // 	return (1);
		// // }
		// i++;
	}
	return (0);
}





int   ft_piping_2(char *line, t_cmd *list)
{
   int   i = 0;
   char **str;

   printf("Let's start\n");
   list = NULL;
   printf("origine line is : %s\n", line);
   str = ft_split_3(line, '|');
   printf("done splitting\n");
   while (str[i])
   {
      list = add_cell(list, str[i], i); // deux cellules, dans chaqune on met str[i]
      i++;
   }
   print_list(list);
   free(list);
   free(str);
   return(i);
}

// init
int	malloc_node(t_cmd	**one_cmd)
{
	t_cmd	*new;
	
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->next = NULL;
	if (!(*one_cmd))
	{
		*one_cmd = new;
		printf("after node\n");
	}
	//new->next = NULL;
	printf("done node\n");
	return (1);
}

int	init_one_cmd(t_cmd *one_cmd)
{
	one_cmd->av = NULL;
	one_cmd->cmd_line = NULL;
	one_cmd->ret = 0;
	one_cmd->builtin = 0;
	one_cmd->pipe = 0;
	one_cmd->fork = 0;
	one_cmd->quote = 0;
	one_cmd->d_quotes = 0;
	one_cmd->heredoc = 0;
	one_cmd->stop = 0;
	one_cmd->type = NOPE;
	one_cmd->file = NULL;
	one_cmd->next = NULL;
	printf("done ft_init_cmd done\n");
	return(1);
}

int	ft_init_each_cmd(t_cmd *one_cmd, int *i, char *line)
{

	if (!malloc_node(&one_cmd))
		return (0);
	if (!init_one_cmd(one_cmd))
		return (0);
	one_cmd->next = NULL;
	(*i) = 0;
	ft_space_skip(line, i);
	return (1);
}

// ft_line_after

char	*ft_line_after(char *line, char buf)
{
	int		i;
	char	*new;

	if (line == NULL)
	{
		new = malloc(sizeof(char) * 2);
		new[0] = buf;
		new[1] = '\0';
		return (new);
	}
	i = ft_strlen(line);
	new = malloc(sizeof(char) * (i + 2));
	i = 0;
	while (line[i])
	{
		new[i] = line[i];
		i++;
	}
	new[i] = buf;
	new[++i] = '\0';
	free(line);
	return (new);
}




// ft_fill_av vs ft_malloc_avs

char *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


int	ft_fill_av(t_cmd *one_cmd, char **new, char *line)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (one_cmd->av[y])
	{
		new[y] = malloc(sizeof(char) * (ft_strlen(one_cmd->av[y]) + 1));
		if (!new[y])
			return (0);
		while (one_cmd->av[y][i])
		{	
			new[y][i] = one_cmd->av[y][i];
			i++;
		}
		new[y][i] = '\0';
		i = 0;
		y++;
	}
	new[y] = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new[y])
		return (0);
	ft_strcpy(new[y], line);
	new[++y] = NULL;
	return (1);
}

void	free_avs(char **avs)
{
	int	i;

	i = 0;
	if (avs)
	{
		while (avs[i])
		{
			if (avs[i])
			{
				free(avs[i]);
				avs[i] = NULL;
			}
			i++;
		}
	}
	free(avs);
	avs = NULL;
}

char	**ft_malloc_avs(t_cmd *one_cmd, int len_tab, char *line)
{
	char	**new;

	if (len_tab == 0)
	{
		if (!(new = malloc(sizeof(char *) * 2)))
			return (0);
		new[0] = malloc(sizeof(char) * (ft_strlen(line) + 1));
		if (!new[0])
			return (0);
		ft_strcpy(new[0], line);
		new[1] = NULL;
		free(line);
		return (new);
	}
	new = malloc(sizeof(char *) * (len_tab + 2));
	if (!new)
		return (0);
	ft_fill_av(one_cmd, new, line);
	free(line);
	free_avs(one_cmd->av);
	return (new);
}


int	ft_len_avs(char **avs)
{
	int	i;

	i = 0;
	if (!avs)
		return (0);
	while (avs[i])
		i++;
	return (i);
}


int	ft_avs(t_cmd *one_cmd, char *line)
{
	int	len_tab;

	len_tab = ft_len_avs(one_cmd->av);
	one_cmd->av = ft_malloc_avs(one_cmd, len_tab, line);
	if (!one_cmd->av)
		return (0);
	return (1);
}





// quote checking + moving forward 
// THINGS TODO : ft_malloc_avs 
// 				ft_line = ft_add_line_after

int	ft_check_2rd_quote(char *line, int c)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i + 1] && line[i + 1] == c)
			return (1);
		i++;
	}
	printf("No 2rd quote detected !!!\n\n\n");// \np final is = %d\n", q);
	return (0);
}

char	*ft_add_2rd_quote(t_cmd *one_cmd, int *i, char *line, char *line_after)
{
	(void)one_cmd;
	if (!ft_check_2rd_quote(&line[*i], '"'))
	{
		printf("ERROR: Double quotes are not safely closed\n");
		one_cmd->stop = 1; //->g_exit_value = ???;
		return (0);
	}
	(*i)++;
	while (line[*i] && line[*i] != '"')
	{
	//	line_after = ft_add_line_after(line_after, line[(*i)]);
		(*i)++;
	}
	return (line_after);
}

char	*ft_d2_quotes(char *line_after, int *i, char *line, t_cmd *one_cmd)
{
	if (line_after)
	{
		//ft_malloc_avs(one_cmd, line_after);
		line_after = NULL;
	}
	return (ft_add_2rd_quote(one_cmd, i, line, line_after));
}
// done double quote //



int	ft_each_cmd(char *line, t_cmd *one_cmd)
{
	int			i;
	char		*buf;
	char		*line_after;
	t_cmd		*tmp;

	(void)buf;

	line_after = NULL;
	if (!ft_init_each_cmd(one_cmd, &i, line))
		return (0);
	tmp = one_cmd;
	
	printf("Let's start\n");
	printf("Orgine line is : %s\n", line);

	while (line[i])
	{
		if (line[i] == ' ')
		{
			//printf("space detecting\n");
			printf("line before [%s]\n", &line[i]);
			ft_space_skip(line, &i);
			//printf("line after [%s]\n", &line[i]);
			return (1);
		}
		else if (line[i] == '"')
		{
			printf("Double quote part 1\n\n");
			line_after = ft_d2_quotes(line_after, &i, line, one_cmd);
			if (tmp->stop == 1)
				return (0);
			if (line_after == 0)
				break ;
			//dollar in quote
			//end of line/quote
			line_after = NULL;
			return (1);
		}
		else if (line[i] == '\'')
		{
			printf("signle quotes\n\n");
			return (1);
		}
		else if (line[i] == '$' && !(line[i + 1] == '?'))
		{
			printf("dollar sign but not $? non plus\n\n");
			return (1);
		}
		else if ((line[i] == '<') || line[i] == '>')
		{
			printf("Redirection\n\n");
			return (1);
		}
		else
		{
			printf("adding into line_after?\n\n");
			return (1);
			/*buf = malloc(sizeof(char) * 2);
			ft_fill(line, &i, buf);
			line_after = ft_line_after(line_after, buf[0]);
			if (!line[i] && line_after)
				ft_malloc_avs(tmp, line_after);*/
		}
	//	free(buf);
	
	}
	return (0);
}






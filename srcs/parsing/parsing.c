/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:43:23 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/04 12:50:23 by thi-phng         ###   ########.fr       */
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
//Step 1: parsing espaces and tabs
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
			mini->i = ft_piping(mini->line, mini->cmd);
			printf("%d\n", mini->i);
			return  (1);
		}
		else
		{
			printf("There's only one cmd! Simple\n");

			printf("line = %s\n", mini->line);
			//mini->cmd->cmd_line = mini->line;
			//printf("cmd_line is : %s\n", mini->cmd->cmd_line);
			
			if (ft_each_cmd(mini->line, mini->cmd))
				return (1);
		}
		return (0);
		// if (mini->line[i] == ' ' || mini->line[i] == '\t')
		// 	i++;
		// if (mini->line[i] == '|')
		// {
		// 	char **str;
		// 	str = ft_split_3(mini->line, '|'); //jhgj
		// 	int j = 0;
		// 	while (str[++j])
		// 		  //list = add_cell(list, str[i], i); // deux cellules, dans chaqune on met str[i]
		// 	printf("%s\n", *str);
		// 	printf("PIPE alert : Don't know what to do yet\n");
		// 	return (1);
		// }
		// if (detect_cmd(&mini->line[i]))
		// {
		// 	i = i + detect_cmd(&mini->line[i]) - 1;
		// 	printf("i now is %d\n", i);
		// //	i++;
		// 	printf("And the rest of the line is : %s \n", &mini->line[i + 1]);
		// 	return (1);
		// }
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
  // t_sep *list;
   //*line = "echo coucou | i'm done bye bye";
   int   i = 0;
   char **str;

   printf("Let's start\n");
   list = NULL;
   printf("origine line is : %s\n", line);
   str = ft_split_3(line, '|');
   printf("done splitting\n");
   while (str[i])
   {
	   //add_number_of pipe [pipe++]
      list = add_cell(list, str[i], i); // deux cellules, dans chaqune on met str[i]
      i++;
   }
   print_list(list);
   free(list);
   free(str);
   return(i);
}


int	ft_each_cmd(char *line, t_cmd *one_cmd)
{
	//int i = 0;
	//char *line_c;
	t_cmd	*tmp;
	
	printf("Let's start\n");
	one_cmd = NULL;
	tmp = one_cmd;
	//ft_init_cmd(cmd);
	printf("Orgine line is : %s\n", line);

	while (line)
	{
		printf("line does exit for now\n");
		// le problem commence //
		//cmd->cmd_line = NULL;
		// if (one_cmd->cmd_line == NULL)
		// 	printf("cmd_line is actually NULLed\n");
		printf("hhihi cmd_line exist, str = %s\n", one_cmd->cmd_line);
		return (1);
	//	i++;
	}
	free(one_cmd->cmd_line);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:38:51 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/01 11:06:49 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/*

int	ft_check_2rd_quote(char *str, int *i, char c)
{
	int j = (*i) + 1;
	printf("JEEEEE RENTREEEEEEE\n\n\n");
	while (str[j])
	{
		printf("str[j]\n = %c\n", str[j]);
		if (str[j] && str[j] == c)
			return (1);
		(j)++;
	}
	return (0);
*/


int ft_check_2rd_quote(char *str, int i, int c)
{
	printf("stringgg now is = %c\n", str[i]);
	while (str[i] != c)
	{
		if (str[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_check_2rd_quote_2(char *str, int a)
{
	char	c;
	int		i;
	int		p;

	i = 0;
	c = a;
	p = 0;
	while (str[i])
	{
		if (str[i] == c)
			p++;
		if (i != 0 && str[i + 1] && str[i + 1] == c)
		{
			p++;
			break ;
		}
		i++;
	}
	printf("\nPRINT p de double quotes = %d\n", p);
	if (p % 2 != 0)
		return (1);
	else
		return (0);
}

void	ft_pass_squote(char *str, int *i)
{
	if (str[(*i) + 1] == 34)
		(*i)++;
	else if (str[(*i) + 1] == ' ')
	{
		(*i)++;
		while (str[(*i)] == ' ')
			(*i)++;
	}
	else if (str[(*i)] == 39 && str[(*i) + 1] && str[(*i) + 1] != ' ')
		(*i)++;
}


// char	*ft_add_double_quote(t_cmd *cmd, int *i, char *line, line)

// // DOUBLE QUOTES principales //
// int	ft_d2_quotes(char *str, int *i, char *line, t_cmd *one_cmd)
// {
// 	if (str)
// 	{
// 		ft_avs(one_cmd, str);
// 		str = NULL;
// 	}
// 	return (ft_add_double_quote(param, i, argv, line));
// }


int	ft_d2_quotes(char *str, int *i, char *line, t_cmd *one_cmd)
{
	(*i)++;
	while (line[*i] && line[*i] != '"')
	{
		str = ft_add_line_after(str, line[(*i)]);
		(*i)++;
	}
	if (str)
	{
		printf("~~~~ Inside str exist, adding in ft_avs  ==>str = %s\n\n", str);
		ft_avs(one_cmd, str);
		//return (1);
	}
	//(*i)++;
	//printf("LINEEEEE DAMMMIt = %s\n", &line[*i]);
	printf("\n\n%d\n\n", *i);
	int a = ft_check_2rd_quote(line, (*i), '"');
	if (a == 0)
	{
		printf("CHECK _2rd_code = %d\n", a);
		printf("\033[0;31m ERROR: Double quotes are not safely closed\033[0m\n");
		one_cmd->stop = 1; //->g_n_exit = ???;
		return (0);
	}
	printf("\033[0;32mok check quote \033[0m\n\n");
	//free(str);
	return (1);
}

//int	ft_add_2rd_s_quote(t_mini *one_cmd, int *i, char *line, char *str)
int	ft_single_quote(char *str, int *i, char *line, t_cmd *one_cmd)
{
	int		start;

	start = (*i);
	(*i)++;
	if (!ft_check_2rd_quote(line, (*i), '\''))
	{
		free(str);
		printf("Error: Second single quote not found\n\n");
		//g_n_exit = ??
		return (0);
	}
	while (line[(*i)] && line[(*i)] != '\'')
	{
		str = ft_add_line_after(str, line[(*i)]);
		(*i)++;
	}
	if (str)
		ft_avs(one_cmd, str);
	return (1);
}

// int	ft_check_2rd_quote(char *str, int c)
// {
// 	int		i;
// 	int		p;

// 	i = 0;
// 	p = 0;
// 	while (str[i])
// 	{
// 		if (i != 0 && str[i + 1] && str[i + 1] == c)
// 		{
// 			p++;
// 			break ;
// 		}
// 		if (str[i] == c)
// 			p++;
// 		i++;
// 	}
// 	if (p % 2 == 0)
// 		return (1);
// 	else if (p % 2 == 1)
// 		return(0);
// 	return (0);
// }


// void	ft_pass_squote(char *str, int *i)
// {
// 	if (str[(*i) + 1] == 34)
// 		(*i)++;
// 	else if (str[(*i) + 1] == ' ')
// 	{
// 		(*i)++;
// 		while (str[(*i)] == ' ')
// 			(*i)++;
// 	}
// 	else if (str[(*i)] == 39 && str[(*i) + 1] && str[(*i) + 1] != ' ')
// 		(*i)++;
// }


// // DOUBLE QUOTES principales //
// // int	ft_d2_quotes(char *str, int *i, char *line, t_cmd *one_cmd)
// // {
// // 	//one_cmd->stop = 0;
// // 	if (ft_check_2rd_quote(&line[*i], '"') == 1)
// // 	{
// // 		printf("ERROR: Double quotes are not safely closed\n");
// // 		one_cmd->stop = 1; //->g_n_exit = ???;
// // 		return (0);
// // 	}
// // 	else
// // 	{
// // 		printf("ok check quote\n\n");
// // 		(*i)++;
// // 		while (line[*i] && line[*i] != '"')
// // 		{
// // 			str = ft_add_line_after(str, line[(*i)]);
// // 			(*i)++;
// // 		}
// // 		printf("3. line_after in 3rd layer is: _%s_\n", str);
// // 		if (str)
// // 		{
// // 			printf("Inside str exist, adding in ft_avs\n");
// // 			ft_avs(one_cmd, str);
// // 			return (1);
// // 		}
// // 	}
// // 	free(str);
// // 	return (1);
// // }

// int	ft_d2_quotes(char *str, int *i, char *line, t_cmd *one_cmd)
// {
// 	//one_cmd->stop = 0;
// 	// if (ft_check_2rd_quote(&line[*i], '"') == 1)
// 	// {
// 	// 	printf("ERROR: Double quotes are not safely closed\n");
// 	// 	one_cmd->stop = 1; //->g_n_exit = ???;
// 	// 	return (0);
// 	// }
// 	// else
// 	{
// 		//printf("ok check quote\n\n");
// 		(*i)++;
// 		while (line[*i] && line[*i] != '"')
// 		{
// 			str = ft_add_line_after(str, line[(*i)]);
// 			(*i)++;
// 		}
// 		printf("3. line_after in 3rd layer is: _%s_\n", str);
// 		if (str)
// 		{
// 			printf("Inside str exist, adding in ft_avs\n");
// 			ft_avs(one_cmd, str);
// 			return (1);
// 		}
// 	}
// 	free(str);
// 	printf("\n\n ATTENTION ft_check_2rd_quote RETURNS : = %d\n\n", ft_check_2rd_quote(&line[*i], '"'));
// 	return (ft_check_2rd_quote(&line[*i], '"'));
// }

// //int	ft_add_2rd_s_quote(t_mini *one_cmd, int *i, char *line, char *str)
// int	ft_single_quote(char *str, int *i, char *line, t_cmd *one_cmd)
// {
// 	int		start;

// 	start = (*i);
// 	(*i)++;
// 	if (!ft_check_2rd_quote(&line[start], '\''))
// 	{
// 		free(str);
// 		printf("Error: Second single quote not found\n\n");
// 		//g_n_exit = ??
// 		return (0);
// 	}
// 	while (line[(*i)] && line[(*i)] != '\'')
// 	{
// 		str = ft_add_line_after(str, line[(*i)]);
// 		(*i)++;
// 	}
// 	if (str)
// 		ft_avs(one_cmd, str);
// 	return (1);
// }

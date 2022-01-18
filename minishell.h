/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:34:43 by thi-phng          #+#    #+#             */
/*   Updated: 2022/01/18 16:18:12 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>


typedef struct s_export
{
	char	*name;
	char	*value;
	struct s_export	*next;
}				t_export;

typedef struct s_env
{
	//char	*user_name;
	char	*PWD;
	char	*OLD_PWD;
	int	exit_value;
	t_export	*export;
	struct s_env	*next;
}				t_env;

int	is_digit(char c);
int	is_alpha(char c);
int	is_valid_var_name(char *av);
char	*ft_strjoin(char *s1, char *s2);
int	ft_strlen(char *s);
char	*cpy_trim(char *s, char from, char to);
char	*ft_strndup(char *s, int n);
int	chpos(const char *s, int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_puterror_fd(char *error, char *s, char *error2);
void	free_tab(char ***line);
t_export *new_export(char *export_name, char *export_data);
void	delete_export(t_export **export_lst, char *export_name);
void add_to_export_lst(t_export **export_lst, char *export_name, char *export_data);
void	printstack(t_env *env);
void	ft_memdel(char **s);
void	ft_free_lst(t_env **head);

#endif

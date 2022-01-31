/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:34:43 by thi-phng          #+#    #+#             */
/*   Updated: 2022/01/31 12:19:19 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <signal.h>


# define SEPARATORS " '\"|><"

// *** // STRUCTURE  // *** //

typedef struct s_export
{
	char			*name;
	char			*value;
	struct s_export	*next;
}				t_export;

typedef enum	e_redirecto
{
	NOPE,
	IN,
	OUT,
	DOUBLE_IN,
	DOUBLE_OUT,
}				t_redirecto;

typedef struct	s_cmd
{
	int				ret;
	int				builtin;
	int				pipe;
	int				heredoc;
	int				stop;
	struct s_cmd	*next;
	
}				t_cmd;

typedef struct s_mini
{
	char			**env;
	char			*line;
	char			**execve;
	int				ret;
	int				builtin;
	int				n_cmd;
	int				fork;
	int				pipes;
	int				heredoc;
	int				stop;
	struct s_mini	*next;
	t_export		*export;
}				t_mini;

extern int		g_nb_exit;

// *** // main  // *** //


//*** Utils ***//
int     	find_me(char c, char *str);
int     	is_token_char(char c);int	is_digit(char c);
int 		is_alpha(char c);
int	    	is_valid_var_name(char *av);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char *s1, char *s2);
int	    	ft_strlen(char *s);
char		*cpy_trim(char *s, char from, char to);
char		*ft_strndup(char *s, int n);
int	    	chpos(const char *s, int c);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_puterror_fd(char *error, char *s, char *error2);
void		free_tab(char ***line);

//*** Builtins ***//
t_export	*new_export(char *export_name, char *export_data);
void		delete_export(t_export **export_lst, char *export_name);
void    	add_to_export_lst(t_export **export_lst, char *export_name, char *export_data);
void		printstack(t_mini *env);
void		ft_memdel(char **s);
void		ft_free_lst(t_mini **head);

//*** PARSING ***//
int	parsing(t_mini *mini);

//*** PIPES ***//

//*** REDIRECTIONS ***//

//*** SIGNAUX ***//

//*** SIMPLE QUOTE ***//

//*** DOUBLE QUOTE ***//

//*** SIGNAL ***//
void    ft_sigint_ctr_c(int sig);
void    ft_sigquit_ctr_d(int sig);
void    ft_ignore(int sig);
void    ft_disable_if_fork(int pid);
void    ft_start_signal(void);


#endif

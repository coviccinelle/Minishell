/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:34:43 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/08 16:41:08 by thi-phng         ###   ########.fr       */
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

typedef struct	s_file
{
	char			*name;
	t_redirecto		type_of_redir;
	struct s_file	*next;
}				t_file;


typedef struct	s_heredoc
{
	char				*eof;
	struct s_heredoc	*next;
}				t_heredoc;

// typedef struct	s_cmd
// {

// }				t_mini;

typedef struct s_mini
{
	char			**env;
	char			*line;
	int				i;
	int				stop;
	char			**av;
	int				ac;
	char			*cmd_line;
	int				n_cmd;
	int				ret;
	int				builtin;
	int				pipe;
	int				fork;
	int				quote;
	int				d_quotes;
	int				heredoc;
	t_redirecto		type;
	t_file			*file;
	struct s_mini	*next;
}				t_mini;

extern int		g_nb_exit;

// *** // main  // *** //
//void		ft_init_mini(t_mini *mini);

//*** Utils ***//
int     	find_me(char c, char *str);
int     	is_token_char(char c);int	is_digit(char c);
int 		is_alpha(char c);
int	    	is_valid_var_name(char *av);
char		**ft_split_3(char	const *s, char c);
char		*ft_strchr(const char *s, int c);
void   		ft_space_skip(char *str, int *i);


//char		*ft_strdup(const char *s1);
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
int			ft_count_quotes(const char *str);
char		*ft_strdup(char *s1);
char		**ft_copy_tab(char **env);
int			ft_strcmp(char *s, char *t);
void		*ft_memcpy(void *dst, const void *src, size_t n);

//*** Builtins ***//
t_export	*new_export(char *export_name, char *export_data);
void		delete_export(t_export **export_lst, char *export_name);
void    	add_to_export_lst(t_export **export_lst, char *export_name, char *export_data);
void		printstack(t_mini *env);
void		ft_memdel(char **s);
void		ft_free_lst(t_mini **head);
int			exec_echo(int ac, char **av);
int			exec_pwd(void);
int			exec_export(int ac, char **av, char ***env);
int			exec_unset(int ac, char **av, char ***env);
void		print_env(char **env);
char		*ft_getenv(char **env, char *name);

void		ft_bzero(void *b, size_t n);
void		*ft_memalloc(size_t size);
void		test_print(char **envp);
void		free_tab(char ***line);
void		free_tabs(char **tabs);
void 		ft_putchar(int c);
void 		ft_putstr(char *s);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		*cpy_trim(char *s, char from, char to);
int 		ft_strncmp(char *s1, char *s2, unsigned int n);
//char *ft_strcat(char *dest, char *src);
int			nb_tabs(char **s);
char		*ft_strdup(char *src);
char		*ft_strcpy(char *dst, char *src);
int			ft_alphabetical_order_tab(char **env);
void		print_tab(char **env);
char		**ft_copy_tab(char **env);
int			ft_unsetenv(char ***env,char *name);
void		print_export(char **tab);



//*** PARSING ***//
int			parsing(t_mini *mini/*, t_cmd *cmd*/);
int 		ft_piping(char *line, t_mini *list);
int			ft_each_cmd(char *line, t_mini *cmd);

t_mini		*add_cell(t_mini *list, char *cmd, int pos);
void		print_list(t_mini *list);



//*** PIPES ***//

//*** REDIRECTIONS ***//

//*** SIGNAUX ***//

//*** SIMPLE QUOTE ***//

//*** DOUBLE QUOTE ***//

//*** SIGNAL ***//
void    ft_sigint_ctr_c(int sig);
void    ft_sigquit_ctr_bs(int sig);
void    ft_ignore(int sig);
void    ft_disable_if_fork(int pid);
void    ft_start_signal(void);


#endif

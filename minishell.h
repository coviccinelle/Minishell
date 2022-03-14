/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:34:43 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/14 14:47:03 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>  
# include <sys/wait.h>
# include <fcntl.h>
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define STDIN 0
# define STDOUT 1
# define EXIT_FAILURE 1
# define NOPE_0 0
# define READONLY_0 1
# define HEREDOC_0 2
# define TRUNC_0 3
# define APPEND_0 4
# define ERROR -1
# define SUCCESS 0
# define CHILD 0
# define REDIR 1
# define PIPE 2
# define SEPARATORS " '\"|><"

extern int	g_exit_value;

typedef struct s_export
{
	char				*name;
	char				*value;
	struct s_export		*next;
}				t_export;

typedef enum e_redir
{
	NOPE,
	READONLY,
	HEREDOC,
	TRUNC,
	APPEND,
}				t_redir;

typedef struct s_file
{
	char			*name;
	int				type;
	struct s_file	*next;
}				t_file;

typedef struct s_param
{
	char	*buf;
	char	*va_2;
	char	*var;
	char	***env;
	int		i;
	int		ret1;
	int		ret2;
	int		ret3;
}		t_param;

typedef struct s_cmd
{
	char			*la;
	int				pid;
	char			**av;
	int				type;
	t_file			*file_in;
	t_file			*file_out;
	t_file			*last_file_in;
	t_file			*last_file_out;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_mini
{
	char			*line;
	t_cmd			*cmd;
}				t_mini;

// *** // main  // *** //
void	ft_init_mini(t_mini **mini);
void	init_shell(void);

//*** Utils ***//
int		find_me(char c, char *str);
char	*ft_itoa(int nb);
int		is_digit(char c);
int		is_alpha(char c);
int		is_valid_var_name(char *av);
char	*ft_strchr(const char *s, int c);
char	**ft_copy_tab(char **env);
void	ft_putchar(int c);
void	ft_putstr(char *s);
void	ft_free_tab(char **tab);
int		ft_len_avs(char **avs);
int		skip_blank(char *str);
void	skip_blank_2(char *str, int *i, t_cmd *tmp, char *line_after);
char	**ft_env_cpy(char **envp);
void	print_mini_avs(t_mini *mini);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
char	*cpy_trim(char *s, char from, char to);
char	*ft_strndup(char *s, int n);
int		chpos(const char *s, int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_puterror_fd(char *error, char *s, char *error2);
void	free_tab(char ***line);
char	*ft_strdup(char *s1);
int		ft_strcmp(char *s, char *t);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		rest_is_blank_2(char *str);
void	avs_and_nul(t_cmd *cmd, char *str);
void	free_tout_mini(t_mini *mini);
void	free_tab_3(char **tab, int nrow);
int		is_dollar(char c);
void	free_one_cmd(t_cmd *cmd);

//*** Builtins ***//
void	ft_memdel(char **s);
void	ft_free_lst(t_mini **head);

int		exec_cd(int ac, char **av, char ***env);
void	call_heredoc(char *eof);
//pwd
int		exec_pwd(void);

/*echo*/
int		is_option_n(char *av);
int		echo(int ac, char **av, int option_n);
int		exec_echo(int ac, char **av);
/*env, export et unset*/
char	*ft_strxjoin(char *s1, char *s2, char *s3);
int		env_realloc_and_append_envvar(char ***env, char *envvar);
char	*find_in_env(char **env, char *name, int *pos);
char	*ft_getenv(char **env, char *name);
int		ft_setenv(char ***env, char *av, char *name, char *value);
int		get_into_export_lst(char ***env, char **av, char **name, \
			char **data);
void	init_tab(char **av, char ***s);
int		exec_export(int ac, char **av, char ***env);
int		ft_unsetenv(char ***env, char *name);
int		exec_unset(int ac, char **av, char ***env);
int		print_env(char **env);
char	*ft_getenv(char **env, char *name);
int		exec_exit(int ac, char **av, int *ret);
void	ft_bzero(void *b, size_t n);
void	*ft_memalloc(size_t size);
void	test_print(char **envp);
void	free_tab(char ***line);
void	ft_putchar(int c);
void	ft_putstr(char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*cpy_trim(char *s, char from, char to);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		nb_tabs(char **s);
char	*ft_strcpy(char *dst, char *src);
int		ft_alphabetical_order_tab(char **env);
int		ft_unsetenv(char ***env, char *name);
void	print_export(char **tab);
int		exec_cmd(int ac, char **av, char ***env, t_mini *mini);
int		exec_builtin(char *builtin, int ac, char **av, char ***env);
int		is_builtin(char *builtin);

//*** PARSING ***//
int		parsing(t_cmd *mini, char *line);
void	ft_init_param(t_param *param, char ***env, int *i);
int		ft_avs(t_cmd *one_cmd, char *line_after);
int		ft_buf(char *argv, int *i, char *buf);
char	*ft_single_quote(int *i, char *line, t_cmd *cmd);
void	free_avs(char **avs);
void	print_list(t_cmd **mini);
void	avs_and_nul_2(t_cmd *cmd, char *str, char *s);

//*** DOUBLE QUOTE ***//
int		ft_check_2rd_quote_2(char *line, int c);
char	*ft_d2_quotes(int *i, t_cmd *cmd, t_mini *mini, char ***env);
char	*dollar_sign(int ac, char **av, char **env);
char	*dolar_2(char *str, int *i, char *line_after, char **envp);
void	ft_pass_squote(char *argv, int *i);
int		quote_pass_2(char *argv, int *i);

//*** REDIRECTION parsing ***//
int		check_redir(char *line, int i);
int		ft_redirec(char *line, int *i, char *str, t_cmd **tmp);
t_file	*ft_last_file(t_file *file);
int		ft_add_file_in(t_cmd **cmd, int *i, char *str, char *line);
int		ft_add_file_out(t_cmd **cmd, int *i, char *str, char *line);
char	*ft_add_line_after(char *line, char buf);
void	free_file(t_file **file);
void	get_redir(t_mini *mini, int *i, t_cmd *cmd);

//*** dolar quote ***//
char	*dolar_quote(char *str, char **envp);
char	*dolar_name(char *str, int *i, char *line_after, t_cmd *cmd);
int		is_blank(int c);
int		is_redir(int c);
void	get_line(t_mini *mini, int *pos, t_cmd *cmd);
t_cmd	*stock_cmds(t_mini *mini, char ***env);
void	ft_each_cmd_3(t_mini *mini, char *str, int *i, t_cmd *cmd);
t_cmd	*stock_cmds_2(t_mini *mini);
int		ft_each_cmd_4(t_mini *mini, int *i, t_cmd **one_cmd, char ***env);
char	*add_char(t_mini *mini, char *str, int c);

//*** PIPES ***//
char	*ft_strndup(char *s, int n);
char	**ft_split(char *s, char sep);
void	print_tab(char **av);
void	print_cmds(t_cmd *cmd);
int		nb_cmds(t_cmd *cmd);
void	safely_exec_bin(char **cmd);
void	safely_pipe_me(int new_pipe_fd[]);
void	safely_fork(int *pid);
void	child_process(t_cmd *cmd, int *fd, char ***env, t_mini *mini);
void	waiting_for_all_children_to_finish_execution(int nb_cmds);
void	run_piped_cmds(t_mini *mini, char ***env);
int		exec_cmd_with_no_pipe(t_mini *mini, char ***env);
void	safely_exec_bin_cmds(char *path, char **av, \
								char **env, int *exit_status);
void	init_1(char ***data, char ***name, char **av);
void	init(int *j, int *c, int *exit_value);
char	*l(char *line);
int		cmp_again(t_cmd *cmd);
void	i_am_your_father(t_mini *mini, t_cmd *cmd, char ***env);

//*** REDIRECTIONS ***//
void	ft_set_direct(char *line, int *i, t_cmd *mini);
void	get_redir_in(t_mini *mini, int i, t_cmd *cmd, char *line);
void	get_redir_out(t_mini *mini, int i, t_cmd *cmd);
void	ft_print_av(t_cmd *mini);

//*** SIGNAUX ***//

//*** SIMPLE QUOTE ***//

//*** SIGNAL ***//
void	ft_sigint_ctr_c(int sig);
void	ft_sigquit_ctr_bs(int sig);
void	ft_ignore(int sig);
void	ft_disable_if_fork(int pid);
void	ft_start_signal(void);

// simple utils
int		is_alnum(int c);
//
void	ft_free_cmds(t_mini *mini);
int		ft_len_cmd(char **str);
void	*ft_memset(void *b, int c, size_t len);
void	free_child(t_mini *mini, char ***env);

#endif

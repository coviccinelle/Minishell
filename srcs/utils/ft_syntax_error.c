
#include "../../minishell.h"


// int	syntax_error(t_data *data, int flag)
// {
// 	data->status = 2;
// 	if (flag == REDIR)
// 		ft_putstr_fd("minishell: redirection syntax error\n", STDERR_FILENO);
// 	else if (flag == PIPE)
// 		ft_putstr_fd("minishell: pipe syntax error\n", STDERR_FILENO);
// 	else
// 		ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
// 	return (ERROR);
// }

// int	skip_diff(char *str)
// {
// 	int	i;
// 	int	quote_type;

// 	i = 1;
// 	quote_type = str[i++];
// 	while (str[i] && str[i] != quote_type)
// 		i++;
// 	return (i);
// }





// // int	skip_blank(char *str)
// // {
// // 	int	i;

// // 	i = 0;
// // 	while (fis_blank(str[i]))
// // 		i++;
// // 	return (i);
// // }

// // int	is_redir(int c)
// // {
// // 	if (c == '<' || c == '>')
// // 		return (1);
// // 	return (0);
// // }

// int	is_pipe_error(char *str)
// {
// 	int	i;

// 	i = 1;
// 	i += skip_blank(&str[i]);
// 	if (!str[i] || str[i] == '|' || is_redir(str[i]))
// 		return (1);
// 	return (0);
// }

// // redir error //


// int	is_redir_error(char *str)
// {
// 	int	i;

// 	i = 1;
// 	if (str[i] == str[i - 1])
// 		i++;
// 	i += skip_blank(&str[i]);
// 	if (!str[i] || is_redir(str[i]) || str[i] == '|')
// 		return (1);
// 	return (0);
// }
// // done redir error

// int	syntax_error(t_mini *mini, int return)
// {
// 	mini->ret_status = 2;
// 	if (return == REDIR)
// 		ft_putstr_fd("minishell: REDIR syntax error\n", STDERR_FILENO);
// 	else if (flag == PIPE)
// 		ft_putstr_fd("minishell: PIPE syntax error\n", STDERR_FILENO);
// 	else
// 		ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
// 	return (ERROR);
// }


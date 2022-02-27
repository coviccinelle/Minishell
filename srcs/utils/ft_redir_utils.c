

#include "../../minishell.h"

void    ft_set_direct(char *line, int *i, t_cmd *cmd)
{
    if (line[*i + 1] == '<' && line[*i] == '<')
    {
        printf("Type of redirection 2\n");
        cmd->type = HEREDOC_0;
        return ;
    }
    else if (line[*i] == '>' && line[(*i) + 1] == '>')
    {   
        printf("Type of redirection 4\n");
        cmd->type = APPEND_0; //d_right
        return ;
    }
    else if (line[*i] == '<' && line[(*i) + 1] != '<')
    {
        printf("Type of redirection 1\n");
        cmd->type = READONLY_0;//LEFT;
        return ;
    }
    else if (line[*i] == '>' && line[(*i) + 1] != '>')
    {
        printf("Type of redirection 3\n");
       cmd->type = TRUNC_0; //RIGHT;
        return ;
    }
}

// void	ft_define_redicretcion(char *argv, int *i, t_parsing *param)
// {
// 	if (argv[(*i) + 1] == '<' && argv[(*i)] == '<')
// 		param->type = DOUBLEIN;
// 	else if (argv[(*i) + 1] == '>' && argv[(*i)] == '>')
// 		param->type = DOUBLEOUT;
// 	else if (argv[(*i) + 1] != '<' && argv[(*i)] == '<')
// 		param->type = IN;
// 	else if (argv[(*i) + 1] != '>' && argv[(*i)] == '>')
// 		param->type = OUT;
// }
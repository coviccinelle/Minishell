

#include "../../minishell.h"

void    ft_set_direct(char *line, int *i, t_cmd *cmd)
{
    if (line[*i + 1] == '<' && line[*i] == '<')
    {
        printf("2\n");
        cmd->type = 2;
        return ;
    }
    else if (line[*i] == '>' && line[(*i) + 1] == '>')
    {   
        printf("4\n");
        cmd->type = 4; //d_right
        return ;
    }
    else if (line[*i] == '<' && line[(*i) + 1] != '<')
    {
        printf("1\n");
        cmd->type = 1;//LEFT;
        return ;
    }
    else if (line[*i] == '>' && line[(*i) + 1] != '>')
    {
        printf("3\n");
       cmd->type = 3; //RIGHT;
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
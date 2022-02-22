

#include "../../minishell.h"

void    ft_set_direct(char *line, int *i, t_cmd *mini)
{
    if (line[*i] == '<' && line[(*i) + 1] == '<')
        mini->type = HEREDOC;
    if (line[*i] == '>' && line[(*i) + 1] == '>')
        mini->type = D_RIGHT;
    if (line[*i] == '<' && line[(*i) + 1] != '<')
        mini->type = LEFT;
    if (line[*i] == '>' && line[(*i) + 1] != '>')
        mini->type = RIGHT;
}


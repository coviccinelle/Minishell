

#include "../../minishell.h"

void    ft_set_direct(char *line, int *i, t_mini *mini)
{
    if (line[*i] == '<' && line[(*i) + 1] == '<')
        mini->type = DOUBLE_IN;
    if (line[*i] == '>' && line[(*i) + 1] == '>')
        mini->type = DOUBLE_OUT;
    if (line[*i] == '<' && line[(*i) + 1] != '<')
        mini->type = IN;
    if (line[*i] == '>' && line[(*i) + 1] != '>')
        mini->type = OUT;
}


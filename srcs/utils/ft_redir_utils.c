

#include "../../minishell.h"

void    ft_set_direct(char *line, int *i, t_file *file)
{
    if (line[*i] == '<' && line[(*i) + 1] == '<')
        file->type = heredoc;
    if (line[*i] == '>' && line[(*i) + 1] == '>')
        file->type = right_2;
    if (line[*i] == '<' && line[(*i) + 1] != '<')
        file->type = left;
    if (line[*i] == '>' && line[(*i) + 1] != '>')
        file->type = right;
}


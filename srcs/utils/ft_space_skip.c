

#include "../../minishell.h"

void    ft_space_skip(char *str, int *i)
{
    while ((str[*i] && str[*i] == ' ')| (str[*i] == '\t'))
        (*i)++;
}
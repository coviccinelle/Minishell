
#include "../../minishell.h"

int	get_ftype_left(t_mini *mini, int *i)
{
	(*i)++;
	if (mini->line[*i] == '<')
	{
		(*i)++;
		return (2);//heredoc
	}
	return (1);// left
}


int	get_ftype_right(t_mini *mini, int *i)
{
	(*i)++;
	if (mini->line[*i] == '>')
	{
		(*i)++;
		return (4);//d_right
	}
	return (3);// right
}


void    get_heredoc(t_mini *mini, int *i)
{
    (void)mini;
    (void)*i;
    printf("Alert : HEREDOC\n"); 
}


#include "../../minishell.h"

void	free_tab2(char **tab)
{
	int	j;
	
	j = 0;
	while (tab[j])
	{
		free(tab[j]);
		j++;
	}
	tab = NULL;
}

void	ft_free_cmds(t_mini *mini)
{
	t_cmd	*cmd;
	t_cmd	*next;

	cmd = mini->cmd;
	if (!cmd)
		return ;
	while (cmd->prev)
		cmd = cmd->prev;
	while (cmd)
	{
		next = cmd->next;
		printf("free tout dans cmd pls\n");
		if (*cmd->av)
			free_tab(&cmd->av);
		cmd = next;
	}
}

void	exit_custom(t_mini *mini, char *str, int n)
{
	(void)str;
	(void)mini;
	(void)n;
	printf("Free tout and exit stp\n");
}

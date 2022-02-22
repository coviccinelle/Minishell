
#include "../../minishell.h"


void print_tab(char **av)
{
	int j;

	j = 0;
	while(av[j])
	{
		printf("%s\n", av[j]);
		j++;
	}
}

void print_mini_avs(t_mini *mini)
{
	t_cmd *cmd;
	int i;

	i = 1;
	cmd = mini->cmd;
	while(cmd)
	{
		printf("		%d commande = \n", i);
		print_tab(cmd->av);
		i++;
		cmd = cmd->next;
	}
}
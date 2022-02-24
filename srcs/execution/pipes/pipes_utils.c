#include "../../../minishell.h"


int  nb_cmds(t_cmd *cmd)
{
	int j;

	j = 0;
	while(cmd)
	{
		cmd = cmd->next;
		j++;
	}
	return (j);
}

void safely_pipe_me(int new_pipe_fd[])
{
	if ((pipe(new_pipe_fd)) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void safely_fork(int *pid)
{
	*pid = fork();
	if (pid  < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

#include "../../minishell.h"


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


void safely_exec_bin(char **cmd) //le moment venu,  ajouter ***env en param
{
	if (execve(cmd[0], cmd, NULL) < 0) //le moment venu, remplacer NULL par *env
	{
		perror((cmd)[0]);
		exit(EXIT_FAILURE);
	}
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

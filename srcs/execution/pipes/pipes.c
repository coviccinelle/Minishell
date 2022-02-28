#include "../../../minishell.h"


void exec_cmd_with_no_pipe(t_mini *mini)
{
	t_cmd *cmd;
	int status;

	cmd = mini->cmd;
	//printf("LA commande a exec est = %s\n\n", cmd->av[0]);
	if (is_builtin(cmd->av[0])) //a remplacer par av[0] apres.
		exec_builtin(cmd->av[0], nb_tabs(cmd->av), cmd->av, &mini->env);
	else
	{
	 	pid_t   father;

	 	father = fork();
	 	if (father > 0)
		{
	 		waitpid(-1, &status, 0);
	 		printf("I AM YOUR FATHER\n");
	 	}
	 	if (father == 0)
	 	{
	 		sleep(1);

	//printf("RESULTAT DE LEXECUTION\n\n\n\n\n");
	 		exec_cmd(nb_tabs(cmd->av), cmd->av, &mini->env);
	 		exit(0);
	 	}
	 }
	
	
}



void	child_process(t_cmd *cmd, int *fd, t_mini *mini)
{
	(void)mini;
	int exit_status;

	exit_status = 0;
   //	printf("child process for cmd->av[0] = %s\n", cmd->av[0]);
	close(READ_END);
    //if (cmd->infile)
    //  dup2(infile, STDIN);
    //  close(infile);
    // unline tmp stdin
	if (cmd->next)
		dup2(WRITE_END, STDOUT);
   	//printf("just before exec, child process for cmd->av[0] = %s\n", cmd->av[0]);
    //	if (cmd->outfile)
    //  get_oufile
	close(WRITE_END);
    	if (is_builtin(cmd->av[0]))
	{
		exit_status = exec_builtin(cmd->av[0], nb_tabs(cmd->av), cmd->av, &mini->env); //mettre un g_exit
		exit(exit_status);
	}
    	else if (!is_builtin(cmd->av[0]))
	{
	 	exit_status = exec_cmd(nb_tabs(cmd->av), cmd->av, &mini->env);
		exit(exit_status);
	}
}

void	waiting_for_all_children_to_finish_execution(pid_t	pid_lst[])
{
	int i;
	int status;

	i = -1;
   // printf("finish exxec");
	dup2(STDOUT, STDIN);
    if (!pid_lst)
		return ;
    //http://manpagesfr.free.fr/man/man2/wait.2.html
    /*
    WIFEXITED(status)
renvoie vrai si le fils s'est terminé normalement, c'est-à-dire par un appel à exit(3) ou _exit(2), ou bien par un retour de main().
WEXITSTATUS(status)
renvoie le code de sortie du fils. Ce code est constitué par les 8 bits de poids faibles de l'argument status que le fils a fourni à exit(3) ou à _exit(2) ou l'argument d'une commande de retour dans main(). Cette macro ne peut être évaluée que si WIFEXITED a renvoyé vrai.

*/
	while (pid_lst[++i] /*&& (!WIFSIGNALED(status))*/)
	{
        
		if (waitpid(pid_lst[i], &status, 0) < -1)
      //  if (waitpid(pid_lst[i], &status, WUNTRACED | WCONTINUED) < -1)
        	{
            		perror("waitpid");
           		 exit(EXIT_FAILURE);
        	}    
	/*	if (WIFEXITED(status))
		    g_exit = WEXITSTATUS(status); //renvoie le code de sortie du fils
        if (WIFSIGNALED(status)) //ici amyplant: if gstatus !=131 gstatus +=128 <= voir pq
            g_exit = WTERMSIG(status); //renvoie signal qui a causé fin du fils
        if (WIFSTOPPED(status) //arrêté par le signal WSTOPSIG
            g_exit = WSTOPSIG(status);
	*/
	}
}

void run_piped_cmds(t_mini *mini, int nb_cmd)
{
	int		fd[2];
	pid_t	new_pid;
    pid_t	pid_lst[nb_cmd];
    int j = 0;
    t_cmd	*cmd;

	cmd = mini->cmd;
	while (cmd)
	{
		safely_pipe_me(fd);
		safely_fork(&new_pid);
		pid_lst[j] = new_pid;
		if (new_pid == 0)
                	child_process(cmd, fd, mini);
		else
		{
			
			close(WRITE_END);
			if (cmd->next)
				dup2(READ_END, STDIN);
			close(READ_END);
		}
		close(READ_END);
		close(WRITE_END);
		cmd = cmd->next;
		j++;
	}
	waiting_for_all_children_to_finish_execution(pid_lst);
}

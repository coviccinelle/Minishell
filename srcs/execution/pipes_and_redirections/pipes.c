#include "../../../minishell.h"


void exec_cmd_with_no_pipe(t_mini *mini)
{
	t_cmd *cmd;
	int status;

	cmd = mini->cmd;
	if (is_builtin(cmd->av[0])) //a remplacer par av[0] apres.
		exec_builtin(cmd->av[0], nb_tabs(cmd->av), cmd->av, &mini->env);
	else
	{
	 	pid_t   father;

	 	father = fork();
	 	if (father > 0)
		{
	 		waitpid(-1, &status, 0);
	 	}
	 	if (father == 0)
	 	{
	 		exec_cmd(nb_tabs(cmd->av), cmd->av, &mini->env);
	 		exit(0);
	 	}
	 }
	
	
}

void	dup_last_file_fd_in(t_cmd *cmd)
{
	t_file *last_file_in;
	t_file *file_in;

	file_in = cmd->file_in;
	last_file_in = ft_last_file(file_in);
	printf("PIPE le dernier fichier IN est : type %d nom = %s\n\n", last_file_in->type,last_file_in->name);
}


int	dup_last_file_fd_out(t_cmd *cmd)
{
	t_file *last_file_out;
	t_file *file_out;
	int	fd;

	fd = 0;
	printf("FONCTION DUP FD OUT\n\n");
	file_out = cmd->file_out;
	last_file_out = ft_last_file(file_out);
	if (last_file_out->type == TRUNC_0)
	    fd = open (last_file_out->name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (last_file_out->type == APPEND_0)
        	fd = open(last_file_out->name, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (fd == -1)
	{
        	perror(last_file_out->name);
        	return(1);
    	}
	dup2(fd, STDOUT);
	close(fd);
	return(0);
//	printf("PIPE le dernier fichier OUT est : type %d nom = %s\n\n", last_file_out->type,last_file_out->name);
}

void	child_process(t_cmd *cmd, int *fd, t_mini *mini)
{
//	(void)mini;
	int exit_status;
//	enum	e_redir	a = TRUNC;
//	enum	e_redir b = APPEND;
//	t_file	*last_file_out = mini->cmd->file_out;

//	if (last_file_out)
//		ft_putstr_fd("il y a un file out\n\n", 0);
	exit_status = 0;
   //	printf("child process for cmd->av[0] = %s\n", cmd->av[0]);
	close(READ_END);
/*	if (cmd->file_in)
	{
		
	}	
*/	
    //if (cmd->infile)
    //  dup2(infile, STDIN);
    //  close(infile);
    // unline tmp stdin
	if (cmd->next)
		dup2(WRITE_END, STDOUT);

	//REDIR
	//dup_last_file_fd_out(cmd);
	
	t_file *last_file_out;
	int	last_file;

	last_file = 0;	
	last_file_out = cmd->last_file_out;
	
//	fprintf(stderr, "saluuuuuuut\n");
	int	d;
	d = 3 ;
	//d = ((int)(last_file_out->type));
	/*if(last_file_out->type == d)
		fprintf(stderr,"\nTRUNC\n");
	d = 4;
	if(last_file_out->type == d)
		fprintf(stderr,"\nAPPEND\n");*/
//	if(last_file_out->type == NULL)
//		fprintf(stderr, "\nNULL\n");
	if (last_file_out->type == TRUNC_0)
	{
		fprintf(stderr, "\nAAAAAAAAA\n");
		last_file = open(last_file_out->name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	}
	else if (last_file_out->type == APPEND_0)
	{
		fprintf(stderr, "ca vaaaaaa\n");
		fprintf(stderr, "%s\n", last_file_out->name);
        	last_file = open(last_file_out->name, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	}

 //       last_file = open("HELLO", O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	dup2(last_file, STDOUT);
	close(last_file);
	//FIN REDIR
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
//	fprintf(stderr, "\nNOOOOOONNNNN\n");
	while (cmd)
	{
		safely_pipe_me(fd);
		safely_fork(&new_pid);
		pid_lst[j] = new_pid;
		if (new_pid == 0)
		{
//			fprintf(stderr, "\nOUIIIIII\n");
                	child_process(cmd, fd, mini);
		}
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

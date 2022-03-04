#include "../../../minishell.h"


int	dup_last_file_fd_out(t_cmd *cmd);
int	dup_last_file_fd_in(t_cmd *cmd);

/*
signal(SIGINT, ft_sigint_ctr_c);
	signal(SIGQUIT, ft_sigquit_ctr_bs);
void    ft_sigint_ctr_c(int sig)
{
    (void)sig;
    write(1, "\n", 1);
	rl_replace_line("", 0); 
    //rl_replace_line NOT VALIDE IN C99
	rl_on_new_line();
	rl_redisplay();
}

void    ft_sigquit_ctr_bs(int sig)
{
    (void)sig;
    printf("\b\b  \b\b");
}
*/

void	call_heredoc(char *eof)
{
	int fd;
	char *input;


	input = NULL;
//pour mieux cacher le fichier eof avant un eventuel cat,  char *filename = ft_strxjoin("/tmp/", eof, "/.heredoc")??
	if (eof == NULL)
		return ;
	fd = open("heredoc",  O_CREAT | O_WRONLY | O_RDONLY | O_TRUNC, 0777);
	if (fd == -1)
		perror(eof);
	while (1)
	{
		input = readline("> ");
		if (input)
		{
			if(strncmp(input, eof, strlen(eof)) != 0) // a remplacer par ft_strncmp 
				ft_putendl_fd(input, fd);
			if (strncmp(input, eof, strlen(eof)) == 0) //idem
					break;
			free(input);
		}
	}
	close(fd);
}

void	exec_builtin_no_pipe(t_mini *mini)
{

	t_cmd *cmd;
	pid_t	f;
	int	status;

	int	fd_out;
	cmd = mini->cmd;
	f = fork();
	if( f != 0)
	{
		if((ft_strcmp(cmd->av[0] , "export") == 0 && cmd->av[1]) || (ft_strcmp(cmd->av[0] , "unset") == 0 && cmd->av[1]))
			exec_builtin(cmd->av[0], nb_tabs(cmd->av), cmd->av, &mini->env);
		waitpid(f, &status , 0);
	}
	else
	{
		if (dup_last_file_fd_in(cmd) == 1) //mevite pb cat infini quand cat <file et file nexiste pas ou echo bonjour <EOF
			exit (1);
		fd_out = dup_last_file_fd_out(cmd);
		exec_builtin(cmd->av[0], nb_tabs(cmd->av), cmd->av, &mini->env);
		close(fd_out);
		exit(1);
	}
}

void exec_cmd_with_no_pipe(t_mini *mini)
{
	t_cmd *cmd;
	int status;
	cmd = mini->cmd;

	if (is_builtin(cmd->av[0]))
		exec_builtin_no_pipe(mini);
	else
	{
	 	pid_t   father;

	 	father = fork();
	 	if (father > 0)
	 		waitpid(-1, &status, 0);
	 	if (father == 0)
	 	{
			if (dup_last_file_fd_in(cmd) == 1)
				exit (1);
			dup_last_file_fd_out(cmd);
	 		exec_cmd(nb_tabs(cmd->av), cmd->av, &mini->env);
	 		exit(0);
	 	}
	 }
}

//void unlink heredocs

int	dup_last_file_fd_in(t_cmd *cmd)
{

	t_file *last_file_in;
	int	last_file;
	t_cmd *cmd2;

	cmd2 = cmd;

	last_file = 0;
	last_file_in = cmd->last_file_in;
	if (cmd->last_file_in == NULL)
		return (0);
	if (last_file_in->type == HEREDOC)
		last_file = open("heredoc", O_RDONLY);
	else
		last_file = open(last_file_in->name, O_RDONLY);
	if (last_file == -1)
	{
        	perror(last_file_in->name);
        	return (1) ;
    	}
	dup2(last_file, 0);
	close(last_file);
	unlink("heredoc");	
	return (0);
}


int	dup_last_file_fd_out(t_cmd *cmd)
{
	t_file *last_file_out;
	int	last_file;

	last_file = 0;	
	last_file_out = cmd->last_file_out;
	if (cmd->last_file_out == NULL)
		return (0);
	if (last_file_out->type == TRUNC_0)
		last_file = open(last_file_out->name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (last_file_out->type == APPEND_0)
        	last_file = open(last_file_out->name, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (last_file == -1)
	{
        	perror(last_file_out->name);
        	return(1);
    	}
	dup2(last_file, STDOUT);
	return(last_file);
}

void	child_process(t_cmd *cmd, int *fd, t_mini *mini)
{
	int exit_status;

	exit_status = 0;

	close(READ_END); //fd[0]
	if (dup_last_file_fd_in(cmd) == 1)
		exit (1);
	if (cmd->next)
		dup2(WRITE_END, STDOUT); //fd[1]
	if (dup_last_file_fd_out(cmd) == 1)
		exit (1);
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

/*	while (cmd2->file_in->next)
	{
		if (cmd2->file_in->type == 2)
			unlink(cmd2->file_in->name);
		cmd2->file_in = cmd2->file_in->next;
	}
*/
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

void close_old_prepare_eventual_new(t_cmd *cmd, int *fd)
{
	close(WRITE_END);
	if (cmd->next)
		dup2(READ_END, STDIN);
	close(READ_END);
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
			close_old_prepare_eventual_new(cmd, fd);
		close(READ_END);
		close(WRITE_END);
		cmd = cmd->next;
		j++;
	}

	waiting_for_all_children_to_finish_execution(pid_lst);

}


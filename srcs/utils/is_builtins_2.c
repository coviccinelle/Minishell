
#include "../../minishell.h"


void	minishell_exec_cmds(t_cmd *cmd, t_mini *mini)
{
		exec_builtin(cmd->av[0], nb_tabs(cmd->av), cmd->av, &mini->env);
}


void	run_builtin(t_mini *mini, t_cmd *cmd)
{
	(void)mini;
	(void)cmd;
	printf("coucou please call Marie-Ines to call her super power builtins and solve this mess\n\n");
}




void	run_execve_2(t_mini *mini, t_cmd *cmd)
{

	(void)cmd;
	(void)mini;
	printf("Please call the super man execve and solve this mess\n");
	//printf("Don't forget to fork hihi\n");
		// pid_t   father;

		// father = fork();
		// if (father > 0)
		// {
		// 	waitpid(-1, &status, 0);
		// 	printf("I AM YOUR FATHER\n");
		// }
		// if (father == 0)
		// {
		// 	sleep(1);
		// 	exec_cmd(nb_tabs(cmd->av), cmd->av, mini->env);
		// 	exit(0);
		// }
		// else
		// 	ft_puterror_fd("minishell: ", "COOOOommand not found : ", cmd->av[0]);
}





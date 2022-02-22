
#include "../../minishell.h"



void	init_cmd(t_cmd *cmd)
{
	cmd->line = NULL;
	cmd->av = NULL;
	cmd->type = NOPE;
	cmd->file = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
}


void	ft_init_mini(t_mini **mini)
{
	// malloc or not?
	printf("1\n");
	(*mini)->pipe = 0;
	printf("2\n");
	(*mini)->line = NULL;
	(*mini)->env = NULL;
	//mini->env = ft_env_cpy(env);
	printf("3\n");
	printf("4\n");
	(*mini)->fork = 0;
	//mini->heredoc = 0;
	printf("5\n");
	(*mini)->ret_status = 0;
	printf("6\n");
	(*mini)->heredoc = NULL;
	printf("done init mini\n");
}


void	init_shell()
{
	printf("\e[1;1H\e[2J");
	printf("Welcome to our mini-tiny-shell made by Marie-Ines and Thao\n");
	printf("Attention: Version demo.00\n");
	printf("        ,----,\n");
    printf("   ___.`      `,\n");
    printf("   `===  D     :\n");
    printf("     `'.      .'\n");
    printf("        )    (                   ,\n");
    printf("       /      \\_________________/|\n");
    printf("      /                          |\n");
    printf("     |         MINISHELL         ;\n");
    printf("     |               _____       /\n");
    printf("     |      \\       ______7    ,'\n");
    printf("     |       \\    ______7     /\n");
    printf("      \\       `-,____7      ,'   by Marie-Ines & Thao\n");
    printf("^~^~^~^`\\                  /~^~^~^~^\n");
    printf("  ~^~^~^ `----------------' ~^~^~^\n");
    printf(" ~^~^~^~^~^^~^~^~^~^~^~^~^~^~^~^~\n");
    printf("\n");
    printf("\n");
    printf("\n");
	printf("");
	char *user_name = getenv("USER");
	printf("Your user_name is : %s\n", user_name);
	sleep(1);
//	printf("\e[1;1H\e[2J");
}

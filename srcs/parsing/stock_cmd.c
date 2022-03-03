#include "../../minishell.h"

// should be main parsing -> pour la norme?
void	get_line(t_mini *mini, int *i, t_cmd *cmd)
{
	//char	*var_val;
	//int		quote_type;

	//var_val = NULL;
	while (mini->line[*i] && !is_redir(mini->line[*i]) && mini->line[*i] != '|')
	{
		cmd->line = ft_add_line_after(cmd->line, mini->line[(*i)++]);
	}
}

t_cmd	*new_elem_cmd(t_mini *mini)
{
	t_cmd	*elem;

	(void)mini;//to free after only
	elem = malloc(sizeof(t_cmd));
	if (!elem)
		//exit_custom(mini, NULL, AUTO);
		printf("Exist and Free mini\n");
	elem->line = NULL;
	elem->av = NULL;
	//elem->type = NOPE;
	elem->type = 0;
	elem->file_in = NULL;
	elem->file_out = NULL;
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

void	add_cmd(t_cmd **cmd_lst, t_cmd *cmd)
{
	t_cmd	*current;

	if (!(*cmd_lst))
	{
		*cmd_lst = cmd;
		return ;
	}
	current = *cmd_lst;
	while (current->next)
		current = current->next;
	current->next = cmd;
	cmd->prev = current;
}


char	*get_var_name(char *s, int *i)
{
	char	*var_name;
	int		k;

	k = 0;
	var_name = NULL;
	while (s[*i] && is_alnum(s[*i]))
	{
		var_name[k] = s[*i + k];
		k++;
	}
	var_name[k] = '\0';
	return (var_name);
}

void	get_var_dollar(t_mini *mini, t_cmd *cmd, char *s, int *i)
{
	char	*var;
	char	*var_name;
	int		k;

	k = 0;
	//var = NULL;
	var_name = get_var_name(s, i);
	var = ft_getenv(mini->env, var_name);
	if (!var)
		var = " ";
	ft_avs(cmd, var);
	free(var);
	free(var_name);
}

int			create_files(int type, char *filename)
{
    int fd;

    fd = -1;
	printf("type de ficher = %d\n", type);
	if (type == TRUNC_0)
	    fd = open (filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (type == APPEND_0)
        fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
  // 	else if (type == READONLY_0)
//		fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
        perror(filename);
        return(1);
    }
    close(fd);
	return (0);
}

t_file    *ft_last_file(t_file *file)
{
    t_file       *p;

    p = file;

    while (p && p->next)
    {
        printf("filename  = %s\n", p->name);
        p = p->next;
    }
    return (p);
}

void    stock_cmds_3(t_cmd *cmd)
{
    t_file *file_out;
    t_file *file_inn;

    file_inn = cmd->file_in;
    file_out = cmd->file_out;
    while ((cmd)->file_in)
    {
        create_files((*cmd).file_in->type, (cmd)->file_in->name);
        (cmd)->file_in = (cmd)->file_in->next;
    }
    while ((cmd)->file_out)
    {
        create_files((*cmd).file_out->type, (cmd)->file_out->name);
        (cmd)->file_out = (cmd)->file_out->next;
    }
    cmd->last_file_in = ft_last_file(file_inn);
    cmd->last_file_out = ft_last_file(file_out);
    if (file_inn != NULL)
        printf("le dernier fichier IN est : type %d nom = %s\n\n", cmd->last_file_in->type, cmd->last_file_in->name);
    if (file_out != NULL)
        printf("le dernier fichier OUT est : type %d nom = %s\n\n", cmd->last_file_out->type, cmd->last_file_out->name);
}

//stock cmd
t_cmd	*stock_cmds(t_mini *mini)
{
	t_cmd	*cmd_lst;
	t_cmd	*cmd;
	int		i;

	cmd_lst = NULL;
	i = 0;
	while (mini->line[i])
	{
		cmd = new_elem_cmd(mini);
		add_cmd(&cmd_lst, cmd);
		while (mini->line[i] && mini->line[i] != '|')
		{
			int a = ft_each_cmd_4(mini, mini->line, &i, &cmd);
			printf("  \nPARSING RETURN= %d\n\033[0;31m", a);
			if (a == 1)
			{
				stock_cmds_3(cmd);
			}
			else
			{
				printf("ERROR: syntax error => free tout\nValuer de retour???\n\n");
			//	mini->stop = 1;
			//	break ;
			}
		}
		//if (cmd->av)
		//	ft_print_av(cmd);
		if (mini->line[i] == '|')
			i++;
	}
	return (cmd_lst);
}
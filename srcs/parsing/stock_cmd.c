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


// int	ft_quote(t_mini *mini, t_cmd *cmd, char *s, int *i)
// {
// 	char	*line_after;

// 	(void)mini; // to use after for $ sign inside quote
// 	line_after = NULL;
// 	if (s[*i] == '"')
// 	{
// 		printf("1_Double quote found\n\n");
// 		printf("where am i ? s[*i] = double quote found : %c\n", s[*i]);
// 		if (!ft_d2_quotes(line_after, i, s, cmd))
// 			return (0);
// 		printf("cmd->av[0] = %s\ncmd->av[1] = %s\n", cmd->av[0], cmd->av[1]);
// 		// if (s[(*i) + 1] == '\0')
// 		// 	return (0) ;
// 		//dollar in quote
// 		if (!quote_pass_2(s, i))
// 			return (0) ;
// 		line_after = NULL;
// 	}
// 	else if (s[*i] == '\'')
// 	{
// 		printf("single quotes\n\n");
// 		printf("line_after = %s\n", line_after);
// 		if (!ft_single_quote(line_after, i, s, cmd))
// 			return (0);
// 		// if (s[(*i) + 1] == '\0')
// 		// 	break ;
// 		ft_pass_squote(s, i);
// 		line_after = NULL;
// 	}
// 	return (1);
// }


// void	get_avs(t_mini *mini, int *i, t_cmd *cmd)
// {
// 	char	*line;
// 	char	*s;
// 	char	*buf;

// 	line = NULL;
// 	s = mini->line;
// 	printf("get_avs : 1.0");
// 	while (s[*i] && !is_redir(s[*i]) && s[*i] != '|' && s[*i] != ' ')
// 	{
// 		if (s[*i] == '$')
// 			get_var_dollar(mini, cmd, s, i);//a fuction to check if variable after $ exist in env + stock avs
// 		else if (s[*i] == '"' || s[*i] == '\'')
// 		{
// 			if (!ft_quote(mini, cmd, s, i)) // call funtion ft_quotes to take all entre les quotes + stock avs
// 			{
// 				printf("ERROR: quote not ok\n");
// 				exit (0);
// 				//exit_custom;
// 			}
// 		}
// 		else
// 		{
// 			printf("mini->line[i] = %c\n", mini->line[*i]);
// 			buf = malloc(sizeof(char) * 2);
// 			ft_buf(s, i, buf);
// 			line = ft_add_line_after(line, buf[0]);
// 			printf("cmd->line = %s\n", line);
// 			if (!s[*i] && line)
// 				ft_avs(cmd, line);
// 			free(buf);
// 		}
// 	}
// }


int			create_files(int type, char *filename)
{
    int fd;

    fd = -1;
	printf("type de ficher = %d\n", type);
	if (type == TRUNC_0)
	    fd = open (filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (type == APPEND_0)
        fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
   	else if (type == READONLY_0)
		fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
        perror(filename);
        return(1);
    }
    close(fd);
	return (0);
}


void	stock_cmds_3(t_cmd *cmd)
{
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
			printf("\n\n\nPARSING RETURN= %d\n", a);
			//if (!ft_each_cmd_4(mini, mini->line, &i, &cmd))
			if (a == 0)
				return (NULL);
				//exit (0);
			stock_cmds_3(cmd);
		}
		if (mini->line[i] == '|')
			i++;
	}
	return (cmd_lst);
}


#include "../../minishell.h"



// void	set_args(t_data *data, int *pos, t_cmd *cmd)
// {
// 	char	*var_val;
	
// 	while (data->str[*pos] && !is_redir(data->str[*pos]) && \
// 	data->str[*pos] != '|')
// 	{
// 		if (data->str[*pos] == '$')
// 			cmd->args = concat_str(data, cmd->args, \
// 			get_var(data, data->str, pos));
// 		else if (check_quote(data->str, *pos))
// 		{
// 			quote_type = data->str[*pos];
// 			cmd->args = add_char(data, cmd->args, data->str[(*pos)++]);
// 			while (data->str[*pos] && data->str[*pos] != quote_type)
// 				cmd->args = add_char(data, cmd->args, data->str[(*pos)++]);
// 			if (data->str[*pos] == quote_type)
// 				cmd->args = add_char(data, cmd->args, data->str[(*pos)++]);
// 		}
// 		else
// 			cmd->args = add_char(data, cmd->args, data->str[(*pos)++]);
// 	}
// }

// should be main parsing
void	get_line(t_mini *mini, int *i, t_cmd *cmd)
{
	//char	*var_val;
	//int		quote_type;

	//var_val = NULL;
	while (mini->line[*i] && !is_redir(mini->line[*i]) && mini->line[*i] != '|')
	{
		//while (cmd->line)
		
		//	ft_each_cmd(mini, pos, cmd);
		
		cmd->line = ft_add_line_after(cmd->line, mini->line[(*i)++]);
		
		// if (mini->line[*pos] == '$')
		// 	//dollarsign
		// 	printf("dollar sign! DO it please\n");
		// else if (check_quote(mini->line, *pos))
		// {
		// 	// quote_type = mini->line[*pos];
		// 	// cmd->line = add_char(mini, cmd->line, mini->line[(*pos)++]);
		// 	// while (mini->line[*pos] && mini->line[*pos] != quote_type)
		// 	// 	cmd->line = add_char(mini, cmd->line, mini->line[(*pos)++]);
		// 	// if (mini->line[*pos] == quote_type)
		// 	// 	cmd->line = add_char(mini, cmd->line, mini->line[(*pos)++]);
		// }
		// else
		// 	cmd->line = add_char(mini, cmd->line, mini->line[(*pos)++]);
	}
}

// void	set_line(t_mini *mini, int *pos, t_cmd *cmd)
// {
// 	char	*var_val;
// 	int		quote_type;

// 	var_val = NULL;
// 	while (mini->line[*pos] && !is_redir(mini->line[*pos]) && \
// 	mini->line[*pos] != '|')
// 	{
// 		if (mini->line[*pos] == '$')
// 			cmd->line = concat_line(mini, cmd->line, \
// 			get_var(mini, mini->line, pos));
// 		else if (check_quote(mini->line, *pos))
// 		{
// 			quote_type = mini->line[*pos];
// 			cmd->line = add_char(mini, cmd->line, mini->line[(*pos)++]);
// 			while (mini->line[*pos] && mini->line[*pos] != quote_type)
// 				cmd->line = add_char(mini, cmd->line, mini->line[(*pos)++]);
// 			if (mini->line[*pos] == quote_type)
// 				cmd->line = add_char(mini, cmd->line, mini->line[(*pos)++]);
// 		}
// 		else
// 			cmd->line = add_char(data, cmd->line, data->line[(*pos)++]);
// 	}
// }



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
	elem->type = NOPE;
	elem->file = NULL;
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


void	get_redir(t_mini *mini, int *i, t_cmd *cmd)
{
	(void)cmd;//will be used later in redirection
	if (mini->line[*i] == '<')
		//get_redir_in(data, i, cmd);
		printf("redirection IN\n");
	else
		printf("Redirection OUT\n");
		//get_redir_out(data, i, cmd);
}


//stock cmd
t_cmd	*stock_cmds_2(t_mini *mini)
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
			i += skip_blank(&mini->line[i]);
			if (is_redir(mini->line[i]))
				get_redir(mini, &i, cmd);
			else
				//ft_each_cmd_2(mini, &i, cmd);
                printf("Need to invent newft_each_cmd_2 with a *i for each char\n");
		}
		if (mini->line[i] == '|')
			i++;
	}
	return (cmd_lst);
}


// stock cmd_list in data
t_cmd	*stock_cmds(t_mini *mini)
{
	t_cmd	*cmd_lst;
	t_cmd	*cmd;
	char	**str;
	int		i;
	int 	k;

	char		*buf;
	char		*line_after;

	(void)buf;
	line_after = NULL;
	cmd_lst = NULL;
	i = 0;
	printf("2. Stocking cmds\n");
	while (mini->line)
	{
		str = ft_split_3(mini->line, '|');
		k = 0;
		printf("Done split mini->line into **str\n");
		while (str[k] && k <= ft_len_avs(str))
		{
			printf("hello inside looopp\n");
			cmd = new_elem_cmd(mini);
			add_cmd(&cmd_lst, cmd);
			//should add av the lastest in here => ready to be executed
			printf("done adding one cmd into the chained list\n");
			while (cmd->line[i])
			{
				i += skip_blank(&cmd->line[i]);
				if (is_redir(cmd->line[i]))
					//get_redir(mini, &i, cmd);
					printf("parsing just for redirection\n");
				else
					ft_each_cmd_3(mini, &cmd->line[i], cmd);
				//i++;
			}
			// if (mini->line[i] == '|')
			// {
			// 	printf("	O____O : PIPE detected:	 mini->lin[i] = %c\n", mini->line[i]);
			// 	i++;
			// }
			k++;
		}
	}
	
	return (cmd_lst);
}


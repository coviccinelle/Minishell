
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
	{
		get_redir_in(mini, *i, cmd);
		printf("redirection IN\n");
	}
	else
	{
		printf("Redirection OUT\n");
		get_redir_out(mini, *i, cmd);
	}
}


// void	set_args(t_data *data, int *pos, t_cmd *cmd)
// {
// 	int		quote_type;

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


int	ft_quote(t_mini *mini, t_cmd *cmd, char *s, int *i)
{
	char	*line_after;

	(void)mini; // to use after for $ sign inside quote
	line_after = NULL;
	if (s[*i] == '"')
		{
			printf("1_Double quote found\n\n");
			printf("where am i ? s[*i] = double quote found : %c\n", s[*i]);
			if (!ft_d2_quotes(line_after, i, s, cmd))
				return (0);
			printf("cmd->av[0] = %s\ncmd->av[1] = %s\n", cmd->av[0], cmd->av[1]);
			// if (s[(*i) + 1] == '\0')
			// 	return (0) ;
			//dollar in quote
			if (!quote_pass_2(s, i))
				return (0) ;
			line_after = NULL;
		}
		else if (s[*i] == '\'')
		{
			printf("single quotes\n\n");
			printf("line_after = %s\n", line_after);
			if (!ft_single_quote(line_after, i, s, cmd))
				return (0);
			// if (s[(*i) + 1] == '\0')
			// 	break ;
			ft_pass_squote(s, i);
			line_after = NULL;
		}
	return (1);
}


void	get_avs(t_mini *mini, int *i, t_cmd *cmd)
{
	char	*line;
	char	*s;
	char	*buf;

	line = NULL;
	s = mini->line;
	while (s[*i] && !is_redir(s[*i]) && s[*i] != '|')
	{
		if (s[*i] == '$')
			get_var_dollar(mini, cmd, s, i);//a fuction to check if variable after $ exist in env + stock avs
		else if (s[*i] == '"' || s[*i] == '\'')
		{
			if (!ft_quote(mini, cmd, s, i)) // call funtion ft_quotes to take all entre les quotes + stock avs
			{
				printf("ERROR: quote not ok\n");
				exit (0);
				//exit_custom;
			}
		}
		else
		{
			buf = malloc(sizeof(char) * 2);
			ft_buf(line, i, buf);
			line = ft_add_line_after(line, buf[0]);
			if (!line[*i] && line)
				ft_avs(cmd, line);
			free(buf);
		}
	}
}

//stock cmd
t_cmd	*stock_cmds_2(t_mini *mini)
{
	t_cmd	*cmd_lst;
	t_cmd	*cmd;
	int		i;

	printf("2.0 Start\n");
	cmd_lst = NULL;
	i = 0;
	while (mini->line[i])
	{
		printf("2.1 Inside mini->line\n");
		cmd = new_elem_cmd(mini);
		printf("2.2 Done add new_elem_cmd\n");
		add_cmd(&cmd_lst, cmd);
		printf("2.3 Done add cmd in cmd_list\n");
		while (mini->line[i] && mini->line[i] != '|')
		{
			i += skip_blank(&mini->line[i]);
			if (is_redir(mini->line[i]))
				get_redir(mini, &i, cmd);
			else
				get_avs(mini, &i, cmd);
              //  printf("Need to invent new ft_each_cmd_2 with a *i for each char\n");
		}
		printf("2.4 Done stocking data in first cmd\n");
		if (mini->line[i] == '|')
			i++;
		printf("2.5 Found a pipe -> new cmd\n\n");
	}
	return (cmd_lst);
}


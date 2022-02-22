
#include "../../minishell.h"

int	get_ftype_left(t_mini *mini, int *i)
{
	(*i)++;
	if (mini->line[*i] == '<')
	{
		(*i)++;
		return (2);//heredoc
	}
	return (1);// left
}


int	get_ftype_right(t_mini *mini, int *i)
{
	(*i)++;
	if (mini->line[*i] == '>')
	{
		(*i)++;
		return (4);//d_right
	}
	return (3);// right
}


void    get_heredoc(t_mini *mini, int *i)
{
    (void)mini;
    (void)*i;
    printf("Alert : HEREDOC\n"); 
}



// char	*get_file_word(t_mini *mini, int *i)
// {
// 	char	*arg;
// 	char	*var_val;

// 	arg = NULL;
// 	var_val = NULL;
// 	*i += skip_blank(&mini->line[*i]);
// 	while (mini->line[*i] && !is_blank(mini->line[*i]) && \
// 	!is_redir(mini->line[*i]) && mini->line[*i] != '|')
// 	{
// 		if (mini->line[*i] == '$')
// 		{
// 			var_val = get_var(mini, mini->line, i);
// 			if (var_val)
// 				arg = concat_str(mini, arg, var_val);
// 		}
// 		else if (check_quote(mini->line, *i))
// 			arg = concat_str(mini, arg, get_quote(mini, mini->line, i));
// 		else
// 			arg = add_char(mini, arg, mini->line[(*i)++]);
// 	}
// 	return (arg);
// }

// char	*get_word(t_mini *mini, int *i)
// {
// 	char	*word;
// 	char	*var_val;

// 	word = NULL;
// 	var_val = NULL;
// 	*i += skip_ws(&mini->line[*i]);
// 	while (mini->line[*i] && !is_blank(mini->line[*i]) && \
// 	!is_redir(mini->line[*i]) && mini->line[*i] != '|')
// 	{
// 		if (mini->line[*i] == '$')
// 		{
// 			var_val = get_var(mini, mini->line, i);
// 			if (var_val)
// 				word = concat_str(mini, word, var_val);
// 			else
// 				return (word);
// 		}
// 		else if (check_quote(mini->line, *i))
// 			word = concat_str(mini, word, get_quote_word(mini, i));
// 		else
// 			word = add_char(mini, word, mini->line[(*i)++]);
// 	}	
// 	return (word);
// }

char	*add_char(t_mini *mini, char *str, int c)
{
	char	*new_str;
	int		len_str;
	int		i;

	(void)mini; // to exit after
	len_str = ft_strlen(str);
	new_str = malloc(len_str + 2);
	if (!new_str)
		//exit_custom(mini, NULL, 500);
		printf("exit_custom\n");
	i = 0;
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	//free((void **)&str);
	return (new_str);
}


char    *get_fname(t_mini *mini, int *i)
{
    char    *ret;
    char    *s;
    int     k;
	char	*buf;

    k = 0;
    ret = NULL;
    s = mini->line;
	printf("inside get_fname\n");
	while (is_blank(mini->line[*i]))
		(*i)++;
   // i += skip_blank(&mini->line[*i]);
	printf("done skip_blank\n");
    //while (s[*i] && !is_blanl(s[*i]) && !is_redir(s[*i] && s[*i] != '|'))
    while (s[*i] && is_alnum(s[*i]))
    {
		buf = malloc(sizeof(char) * 2);
		ft_buf(s, i, buf);
		ret = ft_add_line_after(ret, buf[0]);
		//if (!s[*i] && ret)
		//	ft_avs(cmd, ret);
		free(buf);
       // ret = add_char(mini, ret, s[*i]);
	  // ret = ft_add_line_after(ret, s[*i]);
    }
    ret[k] = '\0';
    return (ret);
}

void    get_redir_in(t_mini *mini, int i, t_cmd *cmd, char *line)
{
	t_file	*current;
	t_file	*new;

	if (line)
		ft_avs(cmd, line);
	printf("start get_redir_in\n");
	line = NULL;
	current = cmd->file;
	printf("0.1 get_redir_in\n");
	new = malloc(sizeof(t_file));
	if (!new)
		//exit_custom(mini, NULL, AUTO);
        printf("Malloc failed (creating a new file node\n");
	printf("0.2 gdone malloc new\n");
	new->next = NULL;
	printf("new-> next = NULL");
	//ft_set_direct(mini->line, &i, new);
	new->type = get_ftype_left(mini, &i);
	printf("0.3 done get_ftype_left_in\n");
    new->name = get_fname(mini, &i);
	printf("0.4 done get_fname_in\n");
	// if (new->type == HEREDOC)
	// 	printf("euhhhh here doc\n");
	// else
	// 	new->word = get_file_word(mini, i);
	if (!cmd->file)
		cmd->file = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void    get_redir_out(t_mini *mini, int i, t_cmd *cmd)
{
    t_file	*current;
	t_file	*new;

	current = cmd->file;
	new = malloc(sizeof(t_file));
	if (!new)
		//exit_custom(mini, NULL, AUTO);
        printf("Malloc failed (creating a new file node\n");
	new->next = NULL;
	new->type = get_ftype_right(mini, &i);
    new->name = get_fname(mini, &i);
	if (!cmd->file)
		cmd->file = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
}
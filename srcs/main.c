/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:33:43 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/21 17:03:42 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	get_pwd()
{
	char	cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("\nCurrent Directory: %s", cwd);
}


int	is_blank(int c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	skip_blank(char *str)
{
	int	i;

	i = 0;
	while (is_blank(str[i]))
		i++;
	return (i);
}

int	is_redir(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}



// int	syntax_error(t_mini *data, int flag)
// {
// 	//data->status = 2;
// 	if (flag == REDIR)
// 		ft_putstr_fd("minishell: redirection syntax error\n", STDERR_FILENO);
// 	else if (flag == PIPE)
// 		ft_putstr_fd("minishell: pipe syntax error\n", STDERR_FILENO);
// 	else
// 		ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
// 	return (ERROR);
// }

int	skip_diff(char *str)
{
	int	i;
	int	quote_type;

	i = 1;
	quote_type = str[i++];
	while (str[i] && str[i] != quote_type)
		i++;
	return (i);
}





// int	skip_blank(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (fis_blank(str[i]))
// 		i++;
// 	return (i);
// }

// int	is_redir(int c)
// {
// 	if (c == '<' || c == '>')
// 		return (1);
// 	return (0);
// }

int	is_pipe_error(char *str)
{
	int	i;

	i = 1;
	i += skip_blank(&str[i]);
	if (!str[i] || str[i] == '|' || is_redir(str[i]))
		return (1);
	return (0);
}

// redir error //


int	is_redir_error(char *str)
{
	int	i;

	i = 1;
	if (str[i] == str[i - 1])
		i++;
	i += skip_blank(&str[i]);
	if (!str[i] || is_redir(str[i]) || str[i] == '|')
		return (1);
	return (0);
}
// done redir error


void    ft_free_all_cmds(t_cmd *cmd)
{
    t_cmd   *tmp;
    
    while (cmd)
    {
		tmp = cmd;
        if (cmd->av)
            ft_free_tab(cmd->av);
        if (cmd->file)
           // ft_free_file_red(cmd->file);
		   printf("Free all files in redirection structure\n");
        cmd = cmd->next;
        free(tmp);
    }
    
}

void    ft_free_mini(t_mini *mini)
{
    t_mini  *tmp;

    if (mini)
    {
        tmp = mini;
        if (mini)
            ft_free_all_cmds(mini->cmd);
        free(tmp);
    }
}


int	syntax_error(t_mini *mini)
{
	(void)mini;
	printf("ERROR : Syntax error\n");
	ft_free_mini(mini);
	// mini->ret_status = 2;
	// if (return == REDIR)
	// 	ft_putstr_fd("minishell: REDIR syntax error\n", STDERR_FILENO);
	// else if (flag == PIPE)
	// 	ft_putstr_fd("minishell: PIPE syntax error\n", STDERR_FILENO);
	// else
	// 	ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
	// return (ERROR);
	return (0);
}



char    *ft_strdup(char *s1)
{
        char    *str;
        int             i;
        int             size;

        size = 0;
        while (s1[size])
        {
                size++;
        }
        str = malloc((size + 1) * sizeof(char));
        if (!str)
                return (NULL);
        i = 0;
        while (s1[i])
        {
                str[i] = s1[i];
                i++;
        }
        str[i] = '\0';
        return (str);
}

char	**ft_env_cpy(char **envp)
{
	int		i;
	int		size;
	char	**env;

	size = 0;
	i = 0;
	while (envp[i++])
		size++;
	env = malloc(sizeof(char *) * (size + 1));
	i = -1;
	while (++i < size)
		env[i] = ft_strdup(envp[i]);
	env[i] = NULL;
	return (env);
}

void	exit_custom(t_mini *mini, char *str, int n)
{
	(void)str;
	(void)mini;
	(void)n;
	printf("Free tout and exit stp\n");
}

char	*ft_readline_input(char *line)
{
	signal(SIGINT, ft_sigint_ctr_c);
	signal(SIGQUIT, ft_sigquit_ctr_bs);
	line = readline("\033[1;33m~🌈 Minishell 🌻$\033[0m ");
	//add_history(line);
	if (!line)
	{
		printf("Oops someone just typed ctr^D?!? Bye, I'm out < 0_0 >\n");
		exit(0);
	}
	return (line);
}


void	init_cmd(t_cmd *cmd)
{
	cmd->line = NULL;
	cmd->av = NULL;
	cmd->stop = 0;
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
	//(*mini)->heredoc = NULL;
	printf("done init mini\n");
}

void	minishell_exec_cmds(t_cmd *cmd, t_mini *mini)
{
	// (void)cmd;
	// int		i;
	// int		ac;
	// int		status;

	// i = 0;
	// ac = nb_tabs(cmd->av);
	// while (i <= ac)
	// {
	// 	printf("Print av[%d] = %s\n\n", i, cmd->av[i]);
	// 	i++;
	// }
	// if (is_builtin(cmd->av[0])) //a remplacer par av[0] apres.
		exec_builtin(cmd->av[0], nb_tabs(cmd->av), cmd->av, &mini->env);
	// else
	// {
	// 	pid_t   father;

	// 	father = fork();
	// 	if (father > 0)
	// 	{
	// 		waitpid(-1, &status, 0);
	// 		printf("I AM YOUR FATHER\n");
	// 	}
	// 	if (father == 0)
	// 	{
	// 		sleep(1);
	// 		exec_cmd(nb_tabs(cmd->av), cmd->av, mini->env);
	// 		exit(0);
	// 	}
	// 	else
	// 		ft_puterror_fd("minishell: ", "COOOOommand not found : ", cmd->av[0]);
	// }
	
}

void	free_tab2(char **tab)
{
	int	j;
	
	j = 0;
	while (tab[j])
	{
		free(tab[j]);
		j++;
	}
	tab = NULL;
}

void	ft_free_cmds(t_mini *mini)
{
	t_cmd	*cmd;
	t_cmd	*next;

	cmd = mini->cmd;
	if (!cmd)
		return ;
	while (cmd->prev)
		cmd = cmd->prev;
	while (cmd)
	{
		next = cmd->next;
		printf("free tout dans cmd pls\n");
		if (*cmd->av)
			free_tab(&cmd->av);
		cmd = next;
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



void	set_redir(t_mini *mini, int *pos, t_cmd *cmd)
{
	(void)cmd;//will be used later in redirection
	if (mini->line[*pos] == '<')
		//set_redir_in(data, pos, cmd);
		printf("redirection IN\n");
	else
		printf("Redirection OUT\n");
		//set_redir_out(data, pos, cmd);
}


// int	check_quote(char *str, int pos)
// {
// 	int	quote_type;

// 	if (str[pos] != '\'' && str[pos] != '\"')
// 		return (0);
// 	quote_type = str[pos++];
// 	while (str[pos])
// 	{
// 		if (str[pos] == quote_type)
// 			return (1);
// 		pos++;
// 	}
// 	return (0);
// }


char	*add_char(t_mini *mini, char *str, int c)
{
	char	*new_str;
	int		len_str;
	int		i;

	len_str = ft_strlen(str);
	new_str = malloc(len_str + 2);
	if (!new_str)
		exit_custom(mini, NULL, 500);
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



// void	set_args(t_data *data, int *pos, t_cmd *cmd)
// {
// 	char	*var_val;
	
// 	while (data->str[*pos] && !is_redir(data->str[*pos]) && \
// 	data->str[*pos] != '|')
// 	{
// 		if (data->str[*pos] == '$')
// 			cmd->args = cocnat_str(data, cmd->args, \
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
void	set_line(t_mini *mini, int *pos, t_cmd *cmd)
{
	//char	*var_val;
	//int		quote_type;

	//var_val = NULL;
	while (mini->line[*pos] && !is_redir(mini->line[*pos]) && mini->line[*pos] != '|')
	{
		//while (cmd->line)
		
		//	ft_each_cmd(mini, pos, cmd);
		
		cmd->line = add_char(mini, cmd->line, mini->line[(*pos)++]);
		
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



int	ft_len_cmd(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	ft_each_cmd_3(t_mini *mini, char *line, t_cmd *one_cmd)
{
	int			i;
	char		*buf;
	char		*line_after;
	t_cmd		*tmp;

	(void)mini;
	(void)buf;
	line_after = NULL;
	i = 0;
	tmp = one_cmd;
	printf("Orgine line is : %s\n", line);
	while (line[i])
	{
		if (line[i] == ' ')
		{
			if (line_after)
				ft_avs(tmp, line_after);
			i++;
			//ft_space_skip(line, &i);
			line_after = NULL;
		}
		else if (line[i] == '"')
		{
			if (!ft_d2_quotes(line_after, &i, line, tmp))
				return (0);
		//	printf("tmp->av[0] = %s\ntmp->av[1] = %s\n", tmp->av[0], tmp->av[1]);
			if (line[i + 1] == '\0')
				break ;
			//dollar in quote
			// if (!mdquote3(line, &i))
			// 	break ;
			line_after = NULL;
		}
		else if (line[i] == '\'')
		{
			printf("Single QUOTES : line_after = %s\n", line_after);
			if (!ft_single_quote(line_after, &i, line, tmp))
				return (0);
			if (line[i + 1] == '\0')
				break ;
			ft_pass_squote(line, &i);
			line_after = NULL;
		}
		else if (line[i] == '$' && !(line[i + 1] == '?'))
		{
			//line_after = ft_dollar_1(line, &i, line_after, one_cmd);
			//line_after = ft_dollar_2(line, &i, line_after, envp);
			printf("dollar sign but not $? non plus\n\n");
			ft_avs(tmp, line_after);
			line_after = NULL;
		}
		else if ((line[i] == '<') || line[i] == '>')
		{
			printf("Redirection\n\n");
		//	if (!ft_pars_redir(line_after, &i, line, tmp)) //idea only
		//		return (0);
		}
		else
		{
			buf = malloc(sizeof(char) * 2);
			ft_buf(line, &i, buf);
			line_after = ft_add_line_after(line_after, buf[0]);
			if (!line[i] && line_after)
				ft_avs(tmp, line_after);
			free(buf);
		}
	}
	return (1);
}




// stock cmd_list in data
t_cmd	*stock_cmds(t_mini *mini)
{
	t_cmd	*cmd_lst;
	t_cmd	*cmd;
	int		i;
	int		k;
	char	**str;
	char		*buf;
	char		*line_after;

	(void)buf;
	line_after = NULL;
	cmd_lst = NULL;
	i = 0;
	k = 0;
	str = NULL;
	printf("2. Stocking cmds\n");
	if (mini->line)
	{
		str = ft_split_3(mini->line, '|');
		printf("done split_3, str[0] = %s\n", str[0]);
	}
	while (str[k] && k < ft_len_cmd(str))
	{
		printf("str[%d] = %s\n", k, str[k]);
		cmd = new_elem_cmd(mini);
		add_cmd(&cmd_lst, cmd);
		printf("done adding one cmd into the chained list\n");
		while (str[k][i])
		{
			i += skip_blank(&str[k][i]);
			// if (find_me('<', str[k]) || find_me('>', str[k]))
			// {
			// 	pars_redir(mini, cmd, str[k]);
			//  	printf("parsing just for redirection\n");
			// 	break ;
			// }	
			if (!ft_each_cmd_3(mini, str[k], cmd))
			{
				printf("ERROR : syntax error : free tout please \n");
				//exit (0);
				ft_syntax_error(cmd, mini);
			}
			break ;
		}
		k++;
	}
	
	return (cmd_lst);
}


int	is_builtin_2(t_mini *mini, t_cmd *cmd)
{
	char	**av;

	(void)mini;
	if (!cmd->line)
		return (0);
	av = ft_split_3(cmd->line, ' ');
	
	if (!av)
		ft_free_tab(av);
	if (!ft_strncmp("echo", av[0], 5) || \
	!ft_strncmp("cd", av[0], 3) || \
	!ft_strncmp("pwd", av[0], 4) || \
	!ft_strncmp("export", av[0], 7) || \
	!ft_strncmp("unset", av[0], 6) || \
	!ft_strncmp("env", av[0], 4) || \
	!ft_strncmp("exit", av[0], 5))
	{
		//ft_free_arr(args);
		ft_free_tab(av);
		return (1);
	}
	ft_free_tab(av);
	return (0);
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
	printf("Don't forget to fork hihi\n");
}


int	ft_syntax_error(t_cmd *mini, t_mini *mini_1)
{
	int	i;
	char	*str;

	i = 0;
	str = mini->line;
	while (str[i])
	{
		if (is_quote_err(&str[i]) != 0)
		{
			printf("\n\nEHHHH: Quote error Get out little rascal\n");
			//return (1);
			return (syntax_error(mini_1/*, REDIR*/));
		}
		if (is_redir(str[i]) && is_redir_error(&str[i]))
			return (syntax_error(mini_1/*, REDIR*/));
		else if (str[i] == '|' && is_pipe_error(&str[i]))
			return (syntax_error(mini_1/*, PIPE*/));
		i++;
	}
	return (SUCCESS);
}

void print_tab(char **av)
{
	int j;

	j = 0;
	while(av[j])
	{
		printf("%s\n", av[j]);
		j++;
	}
}
void print_mini_avs(t_mini *mini)
{
	t_cmd *cmd;
	int i;

	i = 1;
	cmd = mini->cmd;
	while(cmd)
	{
		printf("		%d commande = \n", i);
		print_tab(cmd->av);
		i++;
		cmd = cmd->next;
	}
}
void	mini_run(t_mini *mini)
{
	t_cmd	*cmd;

	printf("1. Start minishell\n");
	mini->cmd = stock_cmds(mini);
	printf("3. Done stocking cmds\n");
	cmd = mini->cmd;
	printf("4. done cmd = mini->cmd\n");
	while (cmd->next)
	{
		if (cmd->av)
		{
			printf("cmd->av EXISTE, mini->line = %s \n", cmd->line);
		}
		if (is_builtin_2(mini, cmd))
		{
			printf("\nBuitins\n");
			//minishell_exec_cmds(cmd, mini);
			run_builtin(mini, cmd);
		}
		else
		{
			printf("\nNot buitins\n");
			run_execve_2(mini, cmd);
		//if (mini->ret_status == 130)
		//	break ;
		}
		cmd = cmd->next;
	}
	//ft_free_cmds(mini);
	printf("Idk, free tout : in main/mini_run\n");
	free(cmd->line);
}

// my_new_version :
void	minishell(char **env)
{
	t_mini		*mini;//data
	char		*line;//data_parsing

	ft_init_mini(&mini);
	mini->env = ft_env_cpy(env);
	init_shell();
	while (42)
	{
		line = ft_readline_input(mini->line);
		add_history(line);
		mini->line = line;
		if (mini->line)
			mini_run(mini);
		print_mini_avs(mini);
		//free(mini);
		//free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	if (ac != 1)
		return (printf("Error: Invalid argument\nHint: only ./minishell\n"), 1);
	minishell(env);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:33:43 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/18 12:36:36 by thi-phng         ###   ########.fr       */
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

int	syntax_error(t_cmd *mini)
{
	(void)mini;
	printf("ERROR : Syntax error\n");
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

t_cmd	*new_elem_cmd(t_mini *mini, char *str)
{
	t_cmd	*elem;

	(void)mini;//to free after only
	elem = malloc(sizeof(t_cmd));
	if (!elem)
		//exit_custom(mini, NULL, AUTO);
		printf("Exist and Free mini\n");
	elem->line = str;
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

// char	*concat_str(t_data *data, char *s1, char *s2)
// {
// 	char	*new_str;
// 	int		i;
// 	int		j;

// 	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
// 	i = 0;
// 	j = 0;
// 	if (!new_str)
// 		exit_custom(data, NULL, AUTO);
// 	while (s1 && s1[i])
// 	{
// 		new_str[i] = s1[i];
// 		i++;
// 	}
// 	while (s2 && s2[j])
// 	{
// 		new_str[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	new_str[i] = '\0';
// 	free_null((void **)&s1);
// 	free_null((void **)&s2);
// 	return (new_str);
// }


int	check_quote(char *str, int pos)
{
	int	quote_type;

	if (str[pos] != '\'' && str[pos] != '\"')
		return (0);
	quote_type = str[pos++];
	while (str[pos])
	{
		if (str[pos] == quote_type)
			return (1);
		pos++;
	}
	return (0);
}


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

void	ft_each_cmd_3(t_mini *mini, char *str, t_cmd *cmd)
{
	char		*buf;
	char		*line_after;
	t_cmd		*tmp;
	char		*line;
	int			i;

	(void)buf;
	(void)mini;//mini will be used for $ in env
	i = 0;
	line_after = NULL;
	cmd->line = str;

	tmp = cmd;
	printf("Orgine line is : %s\n", cmd->line);
	line = cmd->line;
	while (line[i] && line[i] != '|')
	{
		if (line[i] == ' ')
		{
			if (line_after)
				ft_avs(tmp, line_after);
			(i)++;
			//ft_space_skip(line, i);
			line_after = NULL;
		}
		else if (line[i] == '"')
		{
			printf("1_Double quote found\n\n");
			printf("where am i ? line[i] = double quote found : %c\n", line[i]);
			if (!ft_d2_quotes(line_after, &i, line, tmp))
				exit(0) ;
			//printf("tmp->av[0] = %s\ntmp->av[1] = %s\n", tmp->av[0], tmp->av[1]);
			//if (line[(i) + 1] == '\0')
			//	break ;
			//dollar in quote
			// if (!mdquote3(line, &i))
			// 	break ;
			line_after = NULL;
		}
		else if (line[i] == '\'')
		{
			printf("single quotes\n\n");
			printf("line_after = %s\n", line_after);
			if (!ft_single_quote(line_after, &i, line, tmp))
				exit(0);
			if (line[i + 1] == '\0')
				break ;
			ft_pass_squote(line, &i);
			line_after = NULL;
		}
		else
		{
			printf("char = %c\n", line[i]);
			buf = malloc(sizeof(char) * 2);
			ft_buf(line, &i, buf);
			line_after = ft_add_line_after(line_after, buf[0]);
			if (!line[i] && line_after)
				ft_avs(tmp, line_after);
			free(buf);
		}
	}
}

// To pars + stocker every thing in av
//int	ft_init_each_cmd(char c, //)
void	ft_each_cmd_2(t_mini *mini, int *i, t_cmd *cmd)
{
	char		*buf;
	char		*line_after;
	t_cmd		*tmp;
	char		*line;

	(void)buf;
	(void)mini;//mini will be used for $ in env
	line_after = NULL;
	cmd->line = mini->line;

	tmp = cmd;
	printf("Orgine line is : %s\n", cmd->line);
	line = cmd->line;
	while (line[*i] && line[*i] != '|')
	{
		if (line[*i] == ' ')
		{
			if (line_after)
				ft_avs(tmp, line_after);
			(*i)++;
			//ft_space_skip(line, i);
			line_after = NULL;
		}
		else if (line[*i] == '"')
		{
			printf("1_Double quote found\n\n");
			printf("where am i ? line[*i] = double quote found : %c\n", line[*i]);
			if (!ft_d2_quotes(line_after, i, line, tmp))
				exit(0) ;
			//printf("tmp->av[0] = %s\ntmp->av[1] = %s\n", tmp->av[0], tmp->av[1]);
			//if (line[(*i) + 1] == '\0')
			//	break ;
			//dollar in quote
			// if (!mdquote3(line, &i))
			// 	break ;
			line_after = NULL;
		}
		else if (line[*i] == '\'')
		{
			printf("single quotes\n\n");
			printf("line_after = %s\n", line_after);
			if (!ft_single_quote(line_after, i, line, tmp))
				exit(0);
			if (line[*i + 1] == '\0')
				break ;
			ft_pass_squote(line, i);
			line_after = NULL;
		}
		else
		{
			//printf("char = %c\n", line[*i]);
			buf = malloc(sizeof(char) * 2);
			ft_buf(line, i, buf);
			line_after = ft_add_line_after(line_after, buf[0]);
			if (!line[*i] && line_after)
				ft_avs(tmp, line_after);
			free(buf);
		}
	}
}

int	ft_len_cmd(char **str)
{
	int i;

	i = 0;
	while(*str[i])
		i++;
	return (i);
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
			cmd = new_elem_cmd(mini, str[k]);
			add_cmd(&cmd_lst, cmd);
			//should add av the lastest in here => ready to be executed
			printf("done adding one cmd into the chained list\n");
			while (cmd->line[i])
			{
				i += skip_blank(&cmd->line[i]);
				if (is_redir(cmd->line[i]))
					//set_redir(mini, &i, cmd);
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


int	is_builtin_2(t_mini *mini, t_cmd *cmd)
{
	char	**av;

	(void)mini;
	if (!cmd->line)
		return (0);
	av = ft_split_3(cmd->line, ' ');
	
	if (!av)
		ft_free_tab(av);
	// while(*av)
	// {
	// 	cmd->av = &(*av);
	// 	(*av)++;
	// }
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


int	ft_syntax_error(t_cmd *mini)
{
	int	i;
	char	*str;

	i = 0;
	str = mini->line;
	while (str[i])
	{
		if (is_redir(str[i]) && is_redir_error(&str[i]))
			return (syntax_error(mini/*, REDIR*/));
		else if (str[i] == '|' && is_pipe_error(&str[i]))
			return (syntax_error(mini/*, PIPE*/));
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

	//if (ft_syntax_error(mini->cmd) == ERROR)
	// {
	// 	printf("Free tout in mini->line and things you malloc stp!\n");
	// 	return ;
	// }
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


// int	main_2(int ac, char **av, char **envp)
// {
// 	t_mini		mini;
// 	char		*line;
// 	(void)av;

// //	g_n_exit = 0;

// 	//mini = NULL;
// 	ft_init_mini(&mini, envp);
// 	//mini.env = ft_env_cpy(envp);
// 	if (ac != 1)
// 		return (printf("Error: Invalid argument\nHint: only ./minishell\n"), 1);
// 	init_shell();
// 	while (mini.stop == 0)
// 	{
// 		line = ft_readline_input(mini.line);
// 		add_history(line);
// 		while (42)
// 		{
// 			if (parsing(&mini, line))
// 			{
// 				//if (mini.av)
// 				if (mini.next == NULL && mini.av)
// 				{
// 					printf("mini->av exist\n\n");
// 					minishell_exec_cmds(&mini);
// 					mini.av = NULL;
// 					//free_tab(&mini.av);
// 				}
// 				else while (mini.next)
// 				{
// 					printf("there's pipes and lots of cmds\n");
// 				//	mini.av = //une cmd qui gere ca -> ft_pars_piping.c for sure
// 					minishell_exec_cmds(&mini);
// 					mini = *mini.next;
// 				}
// 				break ;
// 			}
// 			else
// 			{
// 				printf("ici 2 parsing return 0 = free\n");
// 				//ft_free_cmd(&mini);
// 				if (mini.av)
// 				{
// 					printf("i'm here mini.av exist and need to be freed\n");
// 					free_tab(&mini.av);
// 				}
// 				//free mini->cmd
// 				break ;
// 			}
// 			free(line);
// 		}
// 	}
// 	return(0);
// }

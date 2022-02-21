/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:53:32 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/21 17:22:01 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int is_alnum(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

// take str from the first char to the next space or < or > or end of str
int    cpy_fname(char *str)
{
    int i;
    i = 0;
    while (str[i] && is_alnum(str[i]))
    {
        if (str[i] == ' ' || str[i] == '<' || str[i] == '>' || str[i] == '\0')
            return (i);
        i++;
    }
    return (0);
}

//return the n str found
char    *cpy_n_char(char *str, int n)
{
    int i;
    char    *ret;

    i = 0;
    ret = NULL;
    while (str[i] && i <= n)
    {
        ret[i] = ret[i];
        i++;
    }
    ret[i] = '\0';
    return (ret);
}

t_file	*new_elem_file(t_mini *mini, t_cmd *cmd, int n, char *name_file)
{
	t_file	*elem;

	(void)mini;//to free after only
    (void)cmd; // to free after maybe?
	elem = malloc(sizeof(t_file));
	if (!elem)
		//exit_custom(mini, NULL, AUTO);
		printf("Exist and Free cmd -> free\n");
	elem->name = name_file;
	elem->type = n;
	elem->next = NULL;
	return (elem);
}

void	add_file_lst(t_file **file_lst, t_file *file)
{
	t_file	*current;

	if (!(*file_lst))
	{
		*file_lst = file;
		return ;
	}
	current = *file_lst;
	while (current->next)
		current = current->next;
	current->next = file;
//	file->prev = current;
}


void    ft_heredoc(char *str)
{
    (void)str;
    printf("Hey! heredoc founded\n\n");
}


// a function to create a node in the redirection structure





char	*pars_redir(t_mini *mini, t_cmd *cmd, char *s)
{
	int     i;
    t_file  *file_lst;
    t_file  *file;
    char    *heredoc;
    char    *line;

    heredoc = NULL;
    file_lst = NULL;
	i = 0;
	while (s[i])
	{
        //check_redir_error(&str[i]);
		if (s[i] == '<' && s[i + 1] && s[i + 1] != '<')
        {
            //create one node in the redirection structure +
            i++;
            skip_blank(&s[i]);
            file = new_elem_file(mini, cmd, 1, cpy_n_char(&s[i], cpy_fname(&s[i])));
            add_file_lst(&file_lst, file);
            i = i + cpy_fname(&s[i]);
    	}
        if (s[i] == '<' && s[i + 1] == '<' && s[i + 2])
        {
            i += 2;
            skip_blank(&s[i]);
            file = new_elem_file(mini, cmd, 2, cpy_n_char(&s[i], cpy_fname(&s[i])));
            add_file_lst(&file_lst, file);
            i = i + cpy_fname(&s[i]);
        }
        if (s[i] == '>' && s[i + 1] != '>')
        {
            i++;
            skip_blank(&s[i]);
            file = new_elem_file(mini, cmd, 3, cpy_n_char(&s[i], cpy_fname(&s[i])));
            add_file_lst(&file_lst, file);
            i = i + cpy_fname(&s[i]);
        }
        if (s[i] == '>' && s[i + 1] == '>' && s[i + 2])
        {
            i++;
            skip_blank(&s[i]);
            heredoc = cpy_n_char(&s[i], cpy_fname(&s[i]));
            ft_heredoc(heredoc);
        }
        else
        {
            line = ft_add_line_after(line, s[i]);
        }
        i++;
    }
    return (line);
    
}

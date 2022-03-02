#include "../../minishell.h"

void	simple_free(t_cmd **st)
{
	t_cmd	*tmp;

	while ((*st))
	{
		tmp = (*st);
		(*st) = (*st)->next;
		free(tmp);
	}
}

void	ft_free_1st(t_cmd **st, int n)
{
	if (n == 1)
	{
		printf("Error\n");
		simple_free(st);
	}
	else
		simple_free(st);
}

void	ft_init_elem(t_cmd *mini)
{
	mini->av = NULL;
	//mini->ac = 0;
	//mini->cmd_line = NULL;
	//mini->n_cmd = 0;
	//mini->ret = 0;
	//mini->builtin = 0;
	//mini->pipe = 0;
	//mini->fork = 0;
	//mini->heredoc = 0;
	//mini->type = NOPE;
  mini->type = 0;
	mini->file_in = NULL;
	mini->file_out = NULL;
	mini->next = NULL;
  mini->prev = NULL;
//	mini->ret_status = 0;
	//mini->heredoc = NULL;
}

t_cmd	*create_cell(char *cmd, t_cmd *cell)
{
//  t_mini	*prev;

//  prev = NULL;
  printf("start inside of creat cell\n\n");
  cell = malloc(sizeof(t_cmd));
  if (!(cell))
  	return (NULL);
  cell->line = cmd;
  cell->next = NULL;
  //prev->next = cell;
  //cell->av = ft_split_3(cmd, ' ');
  return (cell);
}


t_cmd	*add_cell(t_cmd *mini, char *cmd, int pos)
{
  t_cmd	*tmp;
  t_cmd	*new;
  t_cmd  *prev;
  int		  i;

  prev = NULL;
  tmp = mini;
  i = 0;
  new = create_cell(cmd, tmp);
  printf("creating node, node = %s\n\n", cmd);
  if (mini == NULL)
  	return (new);
  while (i < pos)
  {
  	i++;
  	tmp = prev->next;
  	tmp = tmp->next;
    tmp->next = NULL;
  }
  prev->next = new;
  new->next = NULL;
  return (new);
}

int	ft_new_element(t_cmd	**mini, char *line, int i)
{
	t_cmd	*new;
  //t_cmd  *prev;
  int     j;

  j = 0;
  new = add_cell(*mini, line, i);
  //printf("done add _cell\n\n");
  //prev = NULL;
	if ((*mini) == NULL)
  {
    printf("the first node is NULL\n\n");
		(*mini) = new;
  }
	// else while (j <= i)
	// {
  //   printf("in boucle while, j <= i\n\n");
	// 	//tmp = *mini;
	// 	while ((*mini)->next)
	// 		*mini = (*mini)->next;
	// 	(*mini)->next = new;
  //   prev->next = new;
	// }
	new->next = NULL;
	//new->line = line;
	ft_init_elem(new);
	return (1);
}


//Imprimer les cellules :


// faut mettre ft_piping inside of 
void  ft_print_av(t_cmd *mini)
{
  int i = 0;

  //printf("number of av = %d\n", ft_len_avs(mini->av));
  while (mini->av[i] && i < (ft_len_avs(mini->av)))
  {
    printf("list av[%d] is = :%s\n\n", i, mini->av[i]);
    i++;
  }
  printf("done printing av \n\n\n");
}

void	print_list(t_cmd **mini)
{
//  int		i;
  t_cmd  *tmp;

  tmp = *mini;
  //i = 0;
  //printf("inside printf list\n");
  while (tmp)
  {
  	printf("-----------------------------------\n");
  	//printf("| i = %d                            \n", i);
  	printf("| mini->line : %s            \n", tmp->line);
  	printf("-----------------------------------\n\n");

    //printf("Now is time to print every av\n\n");
    ft_print_av(*mini);
  	tmp = tmp->next;
  	//i++;
  }
}

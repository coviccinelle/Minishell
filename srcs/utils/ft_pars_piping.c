#include "../../minishell.h"

// typedef	struct			s_sep
// {
// 	char				*cmd;
// 	struct s_sep		*prev;
// 	struct s_sep		*next;
// 	struct s_pip		*pipcell;
// }						t_sep;


void	simple_free(t_mini **st)
{
	t_mini	*tmp;

	while ((*st))
	{
		tmp = (*st);
		(*st) = (*st)->next;
		free(tmp);
	}
}

void	ft_free_1st(t_mini **st, int n)
{
	if (n == 1)
	{
		printf("Error\n");
		simple_free(st);
	}
	else
		simple_free(st);
}



void	ft_init_elem(t_mini *mini)
{
	mini->env = NULL;
//	mini->i = 0;
	mini->stop = 0;
	mini->av = NULL;
	//mini->ac = 0;
	//mini->cmd_line = NULL;
	//mini->n_cmd = 0;
	//mini->ret = 0;
	//mini->builtin = 0;
	//mini->pipe = 0;
	//mini->fork = 0;
	mini->quote = 0;
	mini->d_quotes = 0;
	//mini->heredoc = 0;
	mini->type = NOPE;
	mini->file = NULL;
	mini->next = NULL;
  mini->prev = NULL;
	mini->ret_status = 0;
	mini->heredoc = NULL;
}

t_mini	*create_cell(char *cmd, t_mini *cell)
{
//  t_mini	*prev;

//  prev = NULL;
  printf("start inside of creat cell\n\n");
  cell = malloc(sizeof(t_mini));
  if (!(cell))
  	return (NULL);
  cell->line = cmd;
  cell->next = NULL;
  //prev->next = cell;
  //cell->av = ft_split_3(cmd, ' ');
  return (cell);
}


t_mini	*add_cell(t_mini *mini, char *cmd, int pos)
{
  t_mini	*tmp;
  t_mini	*new;
  t_mini  *prev;
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

int	ft_new_element(t_mini	**mini, char *line, int i)
{
	//t_mini	*tmp;
	t_mini	*new;
  t_mini  *prev;
  int     j;

  j = 0;
  //new = (t_mini *)malloc(sizeof(t_mini))
  new = add_cell(*mini, line, i);
  printf("done add _cell\n\n");
  prev = NULL;
	if ((*mini) == NULL)
  {
    printf("the first node is NULL\n\n");
		(*mini) = new;
  }
	else while (j <= i)
	{
    printf("in boucle while, j <= i\n\n");
		//tmp = *mini;
		while ((*mini)->next)
			*mini = (*mini)->next;
		(*mini)->next = new;
    prev->next = new;
	}
	new->next = NULL;
	//new->line = line;
	ft_init_elem(new);
	return (1);
}


//Imprimer les cellules :


// faut mettre ft_piping inside of 


void  ft_print_av(t_mini *mini)
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

void	print_list(t_mini **mini)
{
  int		i;
  t_mini  *tmp;

  tmp = *mini;
  i = 0;
  printf("inside printf list\n");
  while (tmp)
  {
  	printf("-----------------------------------\n");
  	printf("| i = %d                            \n", i);
  	printf("| mini->line : %s            \n", tmp->line);
  	printf("-----------------------------------\n\n");

    //printf("Now is time to print every av\n\n");
    //ft_print_av(mini);
  	tmp = tmp->next;
  	i++;
  }
}

// deviding into each cell and add things into **av
int   ft_pars_piping(char *line, t_mini *mini)
{
   int   i = 0;
   char **line_2;
   t_mini *tmp;

  tmp = mini;
   printf("Let's start\n");
   mini = NULL;
   printf("origine big line is : %s\n", line);
   line_2 = ft_split_3(line, '|');
   printf("done splitting\n");
   while (line_2[i] && i <= ft_len_avs(line_2))
   {
      //mini = add_cell(mini, line_2[i], i); // deux cellules, dans chaqune on met str[i]
      if (!ft_new_element(&mini, line_2[i], i))
        return (0);
      printf("done ft_new_element\n");
      //ft_each_cmd(mini->line, mini);
      //print_list(mini);
      i++;
      //mini = prev->next;
      mini = mini->next;
   }
  // printf("cocuou\n\n");
   //mini = mini->prev;
   //printf("mini->line= %s\n", mini->line);
   print_list(&mini);
   free(mini);
   free(line_2);
   return(i);
}




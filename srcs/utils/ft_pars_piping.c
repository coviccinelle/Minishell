#include "../../minishell.h"

// typedef	struct			s_sep
// {
// 	char				*cmd;
// 	struct s_sep		*prev;
// 	struct s_sep		*next;
// 	struct s_pip		*pipcell;
// }						t_sep;

t_mini	*create_cell(char *cmd, t_mini *cell)
{
  // t_mini	*cell;

  cell = malloc(sizeof(t_mini));
  if (!(cell))
  	return (NULL);
  cell->next = NULL;
  cell->line = cmd;
  cell->av = ft_split_3(cmd, ' ');
  return (cell);
}

t_mini	*add_cell(t_mini *mini, char *cmd, int pos)
{
  //t_mini	*prec;
  t_mini	*cur;
  t_mini	*cell;
  int		  i;

  cur = mini;
  i = 0;
  cell = create_cell(cmd, mini);
  if (mini == NULL)
  	return (cell);
  while (i < pos)
  {
  	i++;
  //	prec = cur;
  	cur = cur->next;
  }
  //prec->next = cell;
  cell->next = cur;
  return (mini);
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

void	print_list(t_mini *mini)
{
  int		i;

  i = 0;
  while (mini)
  {
  	printf("-----------------------------------\n");
  	printf("| i = %d                            \n", i);
  	printf("| mini->line : %s            \n", mini->line);
  	printf("-----------------------------------\n\n");

    printf("Now is time to print every av\n\n");
    ft_print_av(mini);
  	mini = mini->next;
  	i++;
  }
}

// deviding into each cell and add things into **av
int   ft_pars_piping(char *line, t_mini *mini)
{
   int   i = 0;
   char **str;

   printf("Let's start\n");
   mini = NULL;
   printf("origine big line is : %s\n", line);
   str = ft_split_3(line, '|');
   printf("done splitting\n");
   while (str[i] && i <= ft_len_avs(str))
   {
      mini = add_cell(mini, str[i], i); // deux cellules, dans chaqune on met str[i]
      //ft_each_cmd(mini->line, mini);
      print_list(mini);
      i++;
      mini = mini->next;
     // return (1);
      // if (ft_each_cmd(mini->line, mini))
      // {
      //   print_list(mini);
      //   i++;
      //   mini = mini->next;
      // }
   }
   //print_list(list);
   free(mini);
   free(str);
   return(i);
}




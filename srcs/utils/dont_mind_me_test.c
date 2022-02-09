#include "../../minishell.h"
#include <string.h> 
#include <stdlib.h>
#include <stdio.h>

// typedef	struct			s_sep
// {
// 	char				*cmd;
// 	struct s_sep		*prev;
// 	struct s_sep		*next;
// 	struct s_pip		*pipcell;
// }						t_sep;

//    ft_slpit    //

// int  ft_strlen(char *str)
// {
//     int i = 0;

//     while (str[i])
//         i++;
//     return (i);
// }




t_mini	*create_cell(char *cmd)
{
  t_mini	*cell;

  cell = malloc(sizeof(t_mini));
  if (!(cell))
  	return (NULL);
  cell->next = NULL;
  cell->line = cmd;
  return (cell);
}

t_mini	*add_cell(t_mini *list, char *cmd, int pos)
{
  t_mini	*prec;
  t_mini	*cur;
  t_mini	*cell;
  int		i;

  cur = list;
  i = 0;
  cell = create_cell(cmd);
  if (list == NULL)
  	return (cell);
  while (i < pos)
  {
  	i++;
  	prec = cur;
  	cur = cur->next;
  }
  prec->next = cell;
  cell->next = cur;
  return (list);
}
//Imprimer les cellules :

void	print_list(t_mini *list)
{
  int		i;

  i = 0;
  while (list)
  {
  	printf("-----------------------------------\n");
  	printf("| i = %d                            \n", i);
  	printf("| list->line : %s            \n", list->line);
  	printf("-----------------------------------\n");
  	list = list->next;
  	i++;
  }
}


int   ft_piping(char *line, t_mini *list)
{
   int   i = 0;
   char **str;

   printf("Let's start\n");
   list = NULL;
   printf("origine line is : %s\n", line);
   str = ft_split_3(line, '|');
   printf("done splitting\n");
   while (str[i])
   {
      list = add_cell(list, str[i], i); // deux cellules, dans chaqune on met str[i]
      i++;
   }
   print_list(list);
   free(list);
   free(str);
   return(i);
}




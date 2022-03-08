#include "../../minishell.h"

void  ft_print_av(t_cmd *mini)
{
  int i = 0;

  while (mini->av[i] && i < (ft_len_avs(mini->av)))
  {
    printf("list av[%d] is = :%s\n\n", i, mini->av[i]);
    i++;
  }
}


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


size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	if (!src)
		return (0);
	i = 0;
	while ((src[i]) && i < dstsize - 1 && dstsize != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

static char			**ft_malloc_error(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static unsigned int	ft_get_nb_strs(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_strs++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_strs++;
	return (nb_strs);
}

static void			ft_get_next_str(char **next_str, unsigned int *next_str_len,
					char c)
{
	unsigned int i;

	*next_str += *next_str_len;
	*next_str_len = 0;
	i = 0;
	while (**next_str && **next_str == c)
		(*next_str)++;
	while ((*next_str)[i])
	{
		if ((*next_str)[i] == c)
			return ;
		(*next_str_len)++;
		i++;
	}
}

void  ft_free_tab(char **tab)
{
   int i = 0;

   while (tab[i])
   {
      free(tab[i]);
      i++;
   }
}

char				**ft_split_3(char const *s, char c)
{
	char			**tab;
	char			*next_str;
	unsigned int	next_str_len;
	unsigned int	nb_strs;
	unsigned int	i;

	if (!s)
		return (NULL);
	nb_strs = ft_get_nb_strs(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (nb_strs + 1))))
		return (NULL);
	i = 0;
	next_str = (char *)s;
	next_str_len = 0;
	while (i < nb_strs)
	{
		ft_get_next_str(&next_str, &next_str_len, c);
		if (!(tab[i] = (char *)malloc(sizeof(char) * (next_str_len + 1))))
			return (ft_malloc_error(tab));
		ft_strlcpy(tab[i], next_str, next_str_len + 1);
		i++;
	}
	tab[i] = NULL;
   //free(tab);
   //ft_free_tab(tab);
	return (tab);
}


//    Done split     //


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




//char * strchr( const char * string, int searchedChar );
// int main()
// {
//     char *str = " hello coucou my friend";

//     printf("%s\n", strchr(str, 'o'));
//     return (0);
// }

// STRTOK : char * strtok( char * string, const char * delimiters ); 

// int main(void)
// {
//     char    *str = "hello coucou my friends";
//     printf("strtok = %s\n", strtok(str, "cou"));
//     return (0);
// }


/*
int main()
{
   char str[80] = "Coucou echo >> hihi.txt | ls token << xeho.txt | cd VietJack";
   const char s[4] = "|><";
   char *token;
   */
   /* lay token dau tien */
   //token = strtok(str, s);
   
   /* duyet qua cac token con lai */
   /*while( token != NULL ) 
   {
      printf( " %s\n", token );
    
      token = strtok(NULL, s);
   }
   
   return(0);
}*/


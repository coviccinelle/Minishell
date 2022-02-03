#include "../../minishell.h"
#include <string.h> 
#include <stdlib.h>
#include <stdio.h>

typedef	struct			s_sep
{
	char				*cmd_sep;
	struct s_sep		*prev;
	struct s_sep		*next;
	struct s_pip		*pipcell;
}						t_sep;

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


t_sep	*create_cell(char *cmd_sep)
{
  t_sep	*cell;

  cell = malloc(sizeof(t_sep));
  if (!(cell))
  	return (NULL);
  cell->prev = NULL;
  cell->next = NULL;
  cell->pipcell = NULL;
  cell->cmd_sep = cmd_sep;
  return (cell);
}

t_sep	*add_cell(t_sep *list, char *cmd_sep, int pos)
{
  t_sep	*prec;
  t_sep	*cur;
  t_sep	*cell;
  int		i;

  cur = list;
  i = 0;
  cell = create_cell(cmd_sep);
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

void	print_list(t_sep *list)
{
  int		i;

  i = 0;
  while (list)
  {
  	printf("-----------------------------------\n");
  	printf("| i = %d                            \n", i);
  	printf("| list->cmd : %s            \n", list->cmd_sep);
  	printf("-----------------------------------\n");
  	list = list->next;
  	i++;
  }
}


// int   main()
// {
//    char  **str;
//    int i = 0;
//    char  *line = "echo coucou | i'm done bye bye";

//    str = ft_split_3(line, '|');

//    while (str[i])
//    {
//       printf("str current is %s\n", str[i]);
//       i++;
//    }
//    free(str);
//    return (0);
// }


int   ft_piping(char *line)
{
   t_sep *list;
   //*line = "echo coucou | i'm done bye bye";
   int   i = 0;
   char **str;

   printf("Let's start\n");
   list = NULL;
   printf("origine line is : %s\n", line);
   str = ft_split_3(line, '|');
   printf("done splitting\n");
   while (str[i])
   {
     // printf("         ~~~                every str ne = %s\n", str[i]);
      list = add_cell(list, str[i], i); // deux cellules, dans chaqune on met str[i]
      i++;
   }
   // i = 0;
   // while (str[i])
   // {
   //    free(str[i]);
   //    i++;
   // }
   //printf("list->cmd_sep = %s\n", list->cmd_sep);
   
   print_list(list);
   free(list);
  // free(line); // no use
   free(str);
   return(0);
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



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

static int  ft_strlen(const char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return (i);
}

static int		count_words(char const *s, char c)
{
	int		i;
	int		words;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == c))
			words++;
		i++;
	}
	return (words);
}

static int		words_len(char const *s, char c)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

static void		*ft_free(char **splitted, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
	return (NULL);
}

static char		**fill(char const *s, int words, char c, char **splitted)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	while (++i < words)
	{
     
		while (*s == ' ')
			s++;
		len = words_len(s, c);
		if (!(splitted[i] = (char *)malloc(sizeof(char) * (len + 1))))
			return (ft_free(splitted, i));
		j = 0;
		while (j <= len)
			splitted[i][j++] = *s++;
		splitted[i][j] = '\0';
      printf("str = ===%s=== ___ and len_str = %d\n", splitted[i], ft_strlen(splitted[i]));
	}
	splitted[i] = NULL;
	return (splitted);
}


char			**ft_split_2(char	const *s, char c)
{
	char	**splitted;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	if (!(splitted = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	splitted = fill(s, words, c, splitted);
	return (splitted);
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
  	printf("| list->cmd_sep : %s            \n", list->cmd_sep);
  	printf("-----------------------------------\n");
  	list = list->next;
  	i++;
  }
}

int   main()
{
   t_sep *list;
   char  *line = "echo coucou | i'm done bye bye";
   int   i = 0;
   char **str;

   printf("Let's start\n");
   list = NULL;
   printf("origine line is : %s\n", line);
   str = ft_split_2(line, '|');
   printf("done splitting\n");
   while (str[i])
   {
     // printf("         ~~~                every str ne = %s\n", str[i]);
      list = add_cell(list, str[i], i); // deux cellules, dans chaqune on met str[i]
      printf("attention : splittinggg \n");
      i++;
   }
   //printf("list->cmd_sep = %s\n", list->cmd_sep);
   
   print_list(list);
   return (0);
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


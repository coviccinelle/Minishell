


#include "../../minishell.h"


// char				**ft_split_3(char const *s, char c)
// {
// 	char			**tab;
// 	char			*next_str;
// 	unsigned int	next_str_len;
// 	unsigned int	nb_strs;
// 	unsigned int	i;

// 	if (!s)
// 		return (NULL);
// 	nb_strs = ft_get_nb_strs(s, c);
// 	if (!(tab = (char **)malloc(sizeof(char *) * (nb_strs + 1))))
// 		return (NULL);
// 	i = 0;
// 	next_str = (char *)s;
// 	next_str_len = 0;
// 	while (i < nb_strs)
// 	{
// 		ft_get_next_str(&next_str, &next_str_len, c);
// 		if (!(tab[i] = (char *)malloc(sizeof(char) * (next_str_len + 1))))
// 			return (ft_malloc_error(tab));
// 		ft_strlcpy(tab[i], next_str, next_str_len + 1);
// 		i++;
// 	}
// 	tab[i] = NULL;
//    //free(tab);
//    //ft_free_tab(tab);
// 	return (tab);
// }


//    Done split     //


// ok ft_plit NO LEAKS with main

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
	//ft_free_tab(tab);
	return (tab);
}
/*
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
//
 }

*/

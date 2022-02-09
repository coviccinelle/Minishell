

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void ft_putchar(int c)
{
	write(1, &c, 1);
}

void ft_putstr(char *s)
{
	int	i;

	i = -1;
	while(s[++i])
		write(1, &s[i], 1);
}


// static int  ft_strlen(const char *str)
// {
//     int i = 0;

//     while (str[i])
//         i++;
//     return (i);
// }

// static int		count_words(char const *s, char c)
// {
// 	int		i;
// 	int		words;

// 	words = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == c))
// 			words++;
// 		i++;
// 	}
// 	return (words);
// }

// static int		words_len(char const *s, char c)
// {
// 	int		i;
// 	int		len;

// 	i = 0;
// 	len = 0;
// 	while (s[i] && s[i] != c)
// 	{
// 		i++;
// 		len++;
// 	}
// 	return (len);
// }

// static void		*ft_free(char **splitted, int words)
// {
// 	int	i;

// 	i = 0;
// 	while (i < words)
// 	{
// 		free(splitted[i]);
// 		i++;
// 	}
// 	free(splitted);
// 	return (NULL);
// }

// static char		**fill(char const *s, int words, char c, char **splitted)
// {
// 	int		i;
// 	int		j;
// 	int		len;

// 	i = -1;
// 	while (++i < words)
// 	{
     
// 		while (*s == ' ')
// 			s++;
// 		len = words_len(s, c);
// 		if (!(splitted[i] = (char *)malloc(sizeof(char) * (len + 1))))
// 			return (ft_free(splitted, i));
// 		j = 0;
// 		while (j < len)
// 			splitted[i][j++] = *s++;
// 		splitted[i][j] = '\0';
//       //  printf("str = ===%s=== ___ and len_str = %d\n", splitted[i], ft_strlen(splitted[i]));
// 	}
// 	splitted[i] = NULL;
// 	return (splitted);
// }


// char			**ft_split_2(char	const *s, char c)
// {
// 	char	**splitted;
// 	int		words;

// 	if (!s)
// 		return (NULL);
// 	words = count_words(s, c);
// 	if (!(splitted = (char **)malloc(sizeof(char *) * (words + 1))))
// 		return (NULL);
// 	splitted = fill(s, words, c, splitted);
// 	return (splitted);
// }

// // int			ft_split(char	const *s, char c)
// // {
// // 	char	**splitted;
// // 	int		words;

// // 	if (!s)
// // 		return (0);
// // 	words = count_words(s, c);
// // 	if (!(splitted = (char **)malloc(sizeof(char *) * (words + 1))))
// // 		return (0);
// // 	splitted = fill(s, words, c, splitted);
// // 	return (ft_strlen(splitted[0]));
// // }

// static int	ft_char_in_set(char c, char const *set)
// {
// 	size_t	i;

// 	i = 0;
// 	while (set[i])
// 	{
// 		if (set[i] == c)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// char		*ft_strtrim(char const *s1, char const *set)
// {
// 	char	*str;
// 	size_t	i;
// 	size_t	start;
// 	size_t	end;

// 	if (!s1)
// 		return (NULL);
// 	start = 0;
// 	while (s1[start] && ft_char_in_set(s1[start], set))
// 		start++;
// 	end = ft_strlen(s1);
// 	while (end > start && ft_char_in_set(s1[end - 1], set))
// 		end--;
// 	if (!(str = (char*)malloc(sizeof(*s1) * (end - start + 1))))
// 		return (NULL);
// 	i = 0;
// 	while (start < end)
// 		str[i++] = s1[start++];
// 	str[i] = 0;
// 	return (str);
// }


// char    *ft_reste_apres_quote(char *str, char c)
// {
//     int i = 0;

//     while (str[i])
//     {
//         if (str[i] == c)
//             return (&str[i + 1]);
//         i++;
//     }
//     return (NULL);
// }

/*
int main(void)
{
   char    *str = "coucou \" hihi ' hu ' ' hihi \"  i love ' you' '";
   char     *str2;
   char    c = '"';

//    //char    *str3 = "hello em be iu";
//     printf("str = %s\n", str);
//     str2 = ft_reste_apres_quote(str, c);

//     printf("the rest after quote = %s\n", str2);//Nouvelle string est le reste a partir de char C

//     printf("retour de split is %d\n", ft_split_2(str2, c));//renvoi ce qui est entre les 2 meme quotes

    

    return (0);
}*/



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_avs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:21:52 by thi-phng          #+#    #+#             */
/*   Updated: 2022/02/10 15:48:21 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



int	ft_buf(char *argv, int *i, char *buf)
{
	if (!argv[(*i)])
		return (0);
	buf[0] = argv[(*i)];
	buf[1] = '\0';
//	(void)line;
	(*i)++;
	return (1);
}

int	ft_fill_av(t_mini *one_cmd, char **new, char *line)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (one_cmd->av[y])
	{
		new[y] = malloc(sizeof(char) * (ft_strlen(one_cmd->av[y]) + 1));
		if (!new[y])
			return (0);
		while (one_cmd->av[y][i])
		{	
			new[y][i] = one_cmd->av[y][i];
			i++;
		}
		new[y][i] = '\0';
		i = 0;
		y++;
	}
	new[y] = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new[y])
		return (0);
	ft_strcpy(new[y], line);
	new[++y] = NULL;
	return (1);
}

void	free_avs(char **avs)
{
	int	i;

	i = 0;
	if (avs)
	{
		while (avs[i])
		{
			if (avs[i])
			{
				free(avs[i]);
				avs[i] = NULL;
			}
			i++;
		}
	}
	free(avs);
	avs = NULL;
}

char	**ft_malloc_avs(t_mini *one_cmd, int len_tab, char *line)
{
	char	**new;

	if (len_tab == 0)
	{
		if (!(new = malloc(sizeof(char *) * 2)))
			return (0);
		new[0] = malloc(sizeof(char) * (ft_strlen(line) + 1));
		if (!new[0])
			return (0);
		ft_strcpy(new[0], line);
		new[1] = NULL;
		free(line);
		return (new);
	}
	new = malloc(sizeof(char *) * (len_tab + 2));
	if (!new)
		return (0);
	ft_fill_av(one_cmd, new, line);
	free(line);
	free_avs(one_cmd->av);
	// if (one_cmd->av)
	//	printf("av existe\n");
	return (new);
}




int	ft_avs(t_mini *one_cmd, char *line_after)
{
	int	len_tab;

	len_tab = ft_len_avs(one_cmd->av);
	//printf("ATTENTION : ft_len_avs is %d\n", ft_len_avs(one_cmd->av));
	one_cmd->av = ft_malloc_avs(one_cmd, len_tab, line_after);
	if (!one_cmd->av)
		return (0);
	//free(line_after);
	return (1);
}


// --------- OLD SPLIT -------//


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



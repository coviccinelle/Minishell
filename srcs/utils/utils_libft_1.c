#include "../../minishell.h"

int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_strlen(char	*s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}
char    *ft_strjoin(char *s1, char *s2)
{
        int     i;
        int     j;
        int     size;
        char    *res;

        i = 0;
        j = 0;
        size = ft_strlen(s1) + ft_strlen(s2) + 1;
        res = (char *)malloc(sizeof(char) * size);
        if (!res || (!s1 && !s2))
                return (NULL);
//      if(s1)
  //              printf("\n S1 : %s\n",s1);
    //    if(s2)
      //         printf("\n S2 : %s\n", s2);
  
	if (!s2)
		return (res = ft_strndup(s1, ft_strlen(s1)));
        else if(!s1)
                return (res = ft_strndup(s2, ft_strlen(s2)));
        while (s1[i])
                res[j++] = s1[i++];
        i = 0;
        while (s2[i])
                res[j++] = s2[i++];
        res[j] = '\0';
        return (res);
}


/*
int	ft_strcmp(char *s, char *t)
{

	while (*s && (*s == *t))
	{
		s++;
		t++;
	}
	return (*s - *t);
}

*/

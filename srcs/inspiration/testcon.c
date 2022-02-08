
#include <stdio.h>
#include <unistd.h>

// int	ft_strchr(const char *s, int c)
// {
// 	char		*str;

// 	//str = (char *)s + ft_strlen(s);
// 	while (*str != c)
// 	{
// 		if (str == s)
// 			return (0);
// 		str++;
// 	}
// 	return (1);
// }


// int		is_type(char *token, int type)
// {
// 	if (token && *token == type)
// 		return (1);
// 	else
// 		return (0);
// }

// int		is_types(char *token, char *types)
// {
// 	if (ft_strchr(types, ' ') && is_type(token, 0))
// 		return (1);
// 	else if (ft_strchr(types, 'X') && is_type(token, 1))
// 		return (1);
// 	return (0);
// }



int	ft_check_2rd_quote(char *argv, int c)
{
	int		i;
	int		q;

	i = 0;
	q = 0;
	while (argv[i])
	{
		if (argv[i + 1] && argv[i + 1] == c)
		{
			q++;
			return (1);
		}
		i++;
	}
	printf("No 2rd quote detected !!! \np final is = %d\n", q);
	return (0);
}


int main()
{
    char *str = "echo coucou con chim cu";
    int c = '\"';
  //  char *types = "hellp";

    //printf("%i\n", ft_strchr(str, c));
    printf("%d\n", ft_check_quote(str, c));
    return (0);
}
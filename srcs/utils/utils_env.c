#include "../minishell.h"

int is_valid_var_name(char *av)
{
		int	i;

		i = -1;
	/*	if (av[0] == '\0')
		{
			printf("no string passed on. probably not an export.\n");
			return (-1); // ret plutot -1 en fonction de ce que met ensuite !! si bug regarder ici
		}
	*/	if (is_digit(av[0]))
			return (0);
		while(av[++i])
		{
			if ((!is_digit(av[i])) && (!is_alpha(av[i]) && av[i] != '_'))
				return (0);
		}
		return(1);
}

int	chpos(const char *s, int c) // pour trouver indice ou jai mon char.
{
	char	*str;

	str = (char *)s;
	while (*str != c)
	{
		if (*str == '\0')
			return (-1);
		str++;
	}
	return (str - s);
}

char	*ft_strndup(char *s, int n)
{
	char *res;
	int	i;

	res = (char *)malloc(sizeof(char) * ft_strlen(s)) + 1;
	i = -1;
	if (!s)
		return (NULL);
	if (!res)
		return (NULL);
//		perror(ENOMEM);
	while (s[++i] && i < n)
		res[i] = s[i];
	res[i] = '\0';
	return (res);
}

char	*cpy_trim(char *s, char from, char to)
{
	int i;
	int j;
	char *d;

	d = NULL;
	i = chpos(s, from);
	j = chpos(s, to);
	if (i == -1 || j == -1)
		return (ft_strndup("", 0));
	if (from == '=')
		i = i + 1;
	d = ft_strndup(&s[i], j);
	return (d);
}


//ajouter ft_strcmp pour mon failure cases dans mon export
/*
#include <string.h>
int main(int ac, char **av)
{
	int	j;
	(void)ac;

	j = 1;

	char *name = cpy_trim(av[j], av[j][0], '=');
	char *value = cpy_trim(av[j], '=', '\0');

	printf("VarName = %s\n", name);

	if (is_valid_var_name(name) == 1)
	{
		printf("Ok nom valable\n");
		printf("Value = %s\n", value);
	}
	else
		printf("Error var name\n");
//	const char *separator = "$";
//	char *export = strtok(av[j], separator);

//	printf("export = %s\n", export);
	return (0);
}

*/

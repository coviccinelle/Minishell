#include "../../minishell.h"












#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

# include <readline/readline.h>
# include <readline/history.h>

#include <unistd.h>

#include <string.h>

void	ft_putendl_fd(char *s, int fd)
{
	if (fd < 0)
		return ;
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
//	write(fd, "\n", 1);
}


void call_heredoc(char *eof)
{
	int fd;
	char *input;


	input = NULL;
	fd = open("/tmp/.heredoc",  O_CREAT | O_WRONLY | O_RDONLY | O_TRUNC, 0777);
	if (fd == -1)
		perror(eof);
	while (1)
	{
		input = readline("> ");
		if (input)
		{
		//	ft_putendl_fd(input, 1);
			if (input[0] == '$' && input[1] != '\0')
					input = getenv(input); //getenv(env, input)ou get expansion de thao. a checker pour "" case avec $
			if (strncmp(input, eof, strlen(eof + 1)) == 0) //plus 1 pour le \n
					break;
			free(input);
		}
	}
	close(fd);
}


int main(int ac, char **av)
{

	int	j;


	(void)ac;
	j = 1;
/*	while(av[j])
	{
		ft_putendl_fd(av[j], 2);
		call_heredoc(av[j]);
		j++;	
	}
*/

		call_heredoc(av[1]);
		call_heredoc(av[2]);
	return (0);
}


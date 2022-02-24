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
	write(fd, "\n", 1);
}


//fonctionne en local. checker avec le parsing de thao. 
//checker que le control d et c marche bien depuis le heredoc
void	call_heredoc(char *eof)
{
	int fd;
	char *input;


	input = NULL;
//pour mieux cacher le fichier eof avant un eventuel cat,  char *filename = ft_strxjoin("/tmp/", eof, "/.heredoc")??
	if (eof == NULL)
		return ;
	fd = open(eof,  O_CREAT | O_WRONLY | O_RDONLY | O_TRUNC, 0777);
	if (fd == -1)
		perror(eof);
	while (1)
	{
		input = readline("> ");
		if (input)
		{
			if(strncmp(input, eof, strlen(eof)) != 0) // a remplacer par ft_strncmp 
				ft_putendl_fd(input, fd);
			if (strncmp(input, eof, strlen(eof)) == 0) //idem
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
	j = 0;
	while(av[++j]) //attention a bien appeler par pipe quand on mixera la fonction avec thao
	{
		call_heredoc(av[j]);
	}

	j = 0;
	while(av[++j])
	{
		unlink(av[j]);
	}
		
	return (0);
}


#include "../../minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int			open_file(int type_of_redir, char *filename, int *fd)
{
	if (type_of_redir == '>')
		fd = open (filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (type_of_redir == 'a') // a modif of course car char ** et pas de strcmp
        	fd = open(O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else if (type_of_redir == '<')
		fd = open(O_RDONLY);
//	if (fd == -1)
//		return (ft_puterror_fd("minishell: ", filename, "no such file or directory\n")); //perror(filename);
	return (0);
}

void	handle_redirection(int type_of_redir, char *last_filename, int *fd_last_file)
{
	int	status;
	pid_t pid;
	
	pid = fork;
	if (pid == 0)
	{
		if (type_of_redir == '<')
			dup2(fd_last_file, STDIN); //replace standard input with input file
		else
			dup2(fd_last_file, STDOUT); //replace standard output with output file
		close(*fd_last_file) //close unused file descriptor
	}
	else
		wait (&status);
	//EXIT = status
}

void redirections()
{
	int j = -1;
	int fd;
	int	is_last_file = FONCTION_QUI_RET_LAST_FILE;
	if (type_of_redir == '<<') // a modif of course car char **
        	//call heredoc ET RETURN (ne t'occupe pas du reste > >> < )
	else
	{
		while (av[++j]) // bon obviously en fonction de thao si next->next ce sera different
		{
			open_file(type_of_redir, filename, &fd); //filename etant av[j]. en fonction parsing thao
			if (!is_last_file) // faire une fonction ? ou if j != ac tout simplement mais en fonction de thao
				close(fd);
		}
		if (is_last_file) // faire une fonction? ou juste ac - 1? en fonction de thao
		    handle_redirection(type_of_redir, filename, &fd); //filename etant av[ac] ou autre en fonction de thao
	}
}

void    heredoc()
{
    
}

void    pipelines()
{

}


int	main(void)
{
//	printf("%d\n\n", file_rights('>'));
//	printf("%d\n\n", file_rights('<'));
//	printf("%d\n\n", file_rights('a'));
	int fd;
	open_file('>', "outputtrunc", &fd);
	open_file('<', "readonly", &fd);
	open_file('a', "outputappend", &fd);
	return (0);
}

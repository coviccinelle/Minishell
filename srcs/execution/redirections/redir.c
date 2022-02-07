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
	if (fd == -1)
		return (ft_puterror_fd("minishell: ", filename, "No such file or directory")); //perror(filename);
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
		else if (type_of_redir == '>' || type_of_redir == '>>')
			dup2(fd_last_file, STDOUT); //replace standard output with output file
		close(*fd_last_file) //close unused file descriptor
	}
	else
		wait (&status);
	//EXIT = status
}


void	close_heredoc(int *pipe_fd[2], char **line)
{
	free(*line);
	dup2(*pipe_fd[0], STDIN);
	close(*pipe_fd[0]);
	close(*pipe_fd[1]);
	return ;
}

//faire une fonction qui retourne le char* inchange si pas trouve dans lenv
void	handle_heredoc()
{
	char	*line;
	int	pipe_fd[2];

	line = NULL;
	if (pipe(pipe_fd) == -1) //est ce que je dois dup qqch?
		perror(pipe_fd); // moui retrouver bon message derreur + est ce que passe qd meme en bas si erreur ?
	while (1)
	{
		line = readline("> ");
		if (line)
		{
			ft_putendl_fd(line, pipe_fd[1]);
			if (line[0] == '$' && line[1] != '\0')
				line = ft_getenv(env, line);
			if (ft_strncmp(line, heredoc->eof, ft_strlen(heredoc->eof)) == 0)
			{
				if (heredoc->next)
					heredoc = heredoc->next;
				else
					break;
			}
			free(line);
		}
	}
	close_heredoc(&pipe_fd, &line);
}

void redirections()
{
	int j = -1;
	int fd;
	if (type_of_redir == '<<') // a modif of course car char **
		handle_heredoc();
	if (type_of_redir == '<' || type_of_redir == '>>' || type_of_redir == '>')
	{
		while (file->next->next) //jusqua avant dernier
		{
			if (type_of_redir == '<' || type_of_redir == '>>' || type_of_redir == '>')
			{	open_file(file->type_of_redir, file->name, &fd);
				close(fd);
			
			file = file->next;
		}
		open_file(file->type_of_redr, file->name, &fd);
		handle_redirection(file->type_of_redir, file->name, &fd);
	}
}


void    pipelines()
{
	//le in prend le dernier out
	while (cmd->next)
	{
		
		cmd = cmd->next;
	}
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

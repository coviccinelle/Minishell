#include "../../../minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
int			open_file(int type_of_redir, char *filename, int *fd)
{
	if (type_of_redir == '>')
		*fd = open (filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (type_of_redir == 'a') // a modif of course car char ** et pas de strcmp
        	*fd = open(O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else if (type_of_redir == '<')
		*fd = open(O_RDONLY);
	if (*fd == -1)
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
		else if (type_of_redir == '>' || type_of_redir == 'a')
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
*/

/*
//faire une fonction qui retourne le char* inchange si pas trouve dans lenv
void	handle_heredoc(int ac, char **av, char **env)
{
	char	*line;
	int	pipe_fd[2];
	int	i;

	i = 0;
	line = NULL;
//	if (pipe(pipe_fd) == -1) //est ce que je dois dup qqch?
//		perror(pipe_fd); // moui retrouver bon message derreur + est ce que passe qd meme en bas si erreur ?
	while (1)
	{
		line = readline("> ");
		if (line)
		{
			ft_putendl_fd(line, pipe_fd[1]);
			if (line[0] == '$' && line[1] != '\0')
				line = ft_getenv(env, line);
		//	if (ft_strncmp(line, heredoc->eof, ft_strlen(heredoc->eof)) == 0)
		//	{
		//		if (heredoc->next)
		//			heredoc = heredoc->next;
		//		else
		//			break;
		//	}

			if (ft_strncmp(line, av[i], ft_strlen(av[i])) == 0)
			{
				if (av[i + 1] != NULL)
					i = i + 1;
				else
					break;
			}
			free(line);
		}
	}
//	close_heredoc(&pipe_fd, &line);
}
*/
/*
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
*/

/*
  #include <sys/types.h>
  #include <sys/wait.h>
#define STDIN 1
#define STDOUT 2
void	handle_redirection(char *type_of_redir, char *last_filename, int *fd_last_file)
{
printf("handle ReDIR \n\n\n");
	int	status;
	pid_t pid;
	
	pid = fork();
	if (pid == 0)
	{
		if (!ft_strcmp(type_of_redir, "<"))
			dup2(*fd_last_file, STDIN); //replace standard input with input file
		if ((!ft_strcmp(type_of_redir, ">")) || (!ft_strcmp(type_of_redir, ">>")))
			dup2(*fd_last_file, STDOUT); //replace standard output with output file
		close(*fd_last_file); //close unused file descriptor
	}
	else
		wait(&status);
	//EXIT = status
}



int			open_file(char *type_of_redir, char *filename, int *fd)
{
	if (!ft_strcmp(type_of_redir, ">"))
		*fd = open (filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (!ft_strcmp(type_of_redir,">>")) // a modif of course car char ** et pas de strcmp
        	*fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (!ft_strcmp(type_of_redir, "<"))
		*fd = open(filename, O_RDONLY);
	if (*fd == -1)
		return (-1);
//ft_puterror_fd("minishell: ", filename, "No such file or directory")); //perror(filename);
	return (0);
}
*/
/*
int	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
	fd = 0;
}
*/
/*
void redirections(int ac, char **av, char **env)
{
	int j = 0;
	int fd;
//	if (type_of_redir == '<<')
//		handle_heredoc();
	while(av[++j]) //jusqua lavant dernier file
	{
		if ((!ft_strncmp(av[j], "<", ft_strlen("<"))) || (!ft_strncmp(av[j], ">>", ft_strlen(">>"))) || (!ft_strncmp(av[j], ">", ft_strlen(">"))))
			open_file(av[j], av[j + 1], &fd);
	//	ft_close(fd);// faire cmd lsof | grep minishell  pour checker que bien closed
		if (j == ac)
			handle_redirection(av[j], av[j + 1], &fd);
	}
}

#define READ_END 0
#define WRITE_END 1
void	run_pipe(char **av)
{
	const int READ_END;
	const int WRITE_END;

	READ_END = 0;
	WRITE_END = 1;
	int	pipes[2];

	pipe(pipes);
	child = fork();
	if (((int)child) == -1)
	{
		close(pipes[READ_END]);
		close(pipes[WRITE_END]);
		perror("fork error\n");
		break;
	}
	else if (child == 0)
	{
		dup2(pipes[WRITE_END], STDOUT_FILENO);
		close(pipes[READ_END]);
		execve(av[0], &av[1], NULL);
		perror("error\n");
		break;
	}
	//parent
	dup2(pipes[READ_END], STDIN_FILENO);
	close(pipes[WRITE_END]);
	wait(NULL);
	execve(av[0], &av[1], NULL);
	return ;
	
}


int	main(int ac, char **av, char **env)
{
//	printf("%d\n\n", file_rights('>'));
//	printf("%d\n\n", file_rights('<'));
//	printf("%d\n\n", file_rights('a'));

	//handle_heredoc(ac, av, env);
//	redirections(ac, av, env);

	pid_t	child;

	child = -1;
	child = fork();
	if (((int)child) == -1)
		perror("fork error\n");
	if (child == 0)
	{
		run_pipe(av);
		perror("error");
		break ;
	}
	wait(NULL); 
		
	return (0);
}
*/

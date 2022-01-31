#include "../../minishell.h"

const int   file_rights(int type_of_redir)
{
    const int   rights;

    rights = 0;
	if (type_of_redir = '>')
		rights = O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU;
	else if (type_of_redir = '>>')
        rights = O_CREAT | O_WRONLY | O_APPEND, S_IRWXU;
	else if (type_of_redir = '<')
        rights = O_RDONLY;
	return (rights);
}

//faire une fonction ou cree tous les fichiers inutiles + le dernier fichier
// faire une fonction ou dup uniquement le dernier fichier et execute laction demandee/ la met  dans le dernier fichier
//faire une fonction pour checker les file permissions et autres messages derreur
//

void redirections()
{
	int j = -1;
	int fd;
	if (type_of_redir = '<<')
        	//call heredoc ET RETURN (ne t'occupe pas du reste > >> < )
	else
	{
		while (av[++j]) // bon obviously en fonction de thao si next->next ce sera different
			open_file(type_of_redir, filename, &fd); //filename etant av[j]. en fonction parsing thao
		if (is_last_file) // faire une fonction? ou juste ac - 1? en fonction de thao
		    handle_redirection(filename, fd); //filename etant av[ac] ou autre en fonction de thao
	}
}

void    heredoc()
{
    
}
void    pipelines()
{

}


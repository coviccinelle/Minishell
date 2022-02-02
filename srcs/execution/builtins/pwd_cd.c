#include "../../../minishell.h"

int exec_pwd(void) 
{
	char *pwd;

	pwd = getcwd(NULL, 0); // si sur linux sinon il faut remplacer NULL et 0
	if (pwd)
	{
		ft_putendl_fd(pwd, 1); //Si la taille du chemin absolu du répertoire de travail en cours, caractère nul de fin compris, dépasse size octets, la fonction renvoie NULL et errno contient le code d'erreur ERANGE. Une application doit détecter cette erreur et allouer un tampon plus grand si besoin est.
		ft_memdel(&pwd);
		return (EXIT_SUCCESS);
	}
	else if (!pwd)
		return (EXIT_FAILURE); 
	//update it to env PWD=
	return (EXIT_SUCCESS);
}


/*
void	exec_cd(int ac, char **av)
{

	char	*current_path;
	char	*new_path;

	current_path = getcwd(NULL, 0);
	if (ac > 2)
		return (ft_puterror_fd("bash: ", "cd: ", "too many arguments"));
	if ((ac == 1) || (ac == 2 && !ft_strcmp(av[2][0], "~")))
		new_path = ft_getenv(env, "HOME");
	else if (ac == 2 && !ft_strcmp(av[2], "-"))
	{
		new_path = ft_getenv(env, "OLDPWD");
		printf("%s\n", new_path);
	}
	else if (ac == 2 && pas trouve dossier (av[1]))
		ft_puterror_fd("cd: ", "no such file or directory: ", av[1]);
	else if (ac == 2 && !is_dir(av[1])) // fd=open(av[1], O_WROLNLY); ??
		ft_puterror_fd("cd: ", "not a directory: ", av[1]);
	else if (ac == 2 && is_dir(av[1]))
		new_path = ??

	a la fin
	chdir(new_path);
	ft_setenv(&env, "PWD", new_path);
	ft_setenv(&env, "OLDPWD", current_path);

}
*/
/*
#include <unistd.h>
int	main(int ac, char **av)
{
//	exec_pwd();
	chdir(av[1]); // pourquoi ne fonctionne pas ??
	return (0);
}
*/
/*
#include<unistd.h> 

int main(int ac, char **av) 
{

  // changing the current
  // working directory(cwd)
  // to /usr
  //if (chdir("/usr") != 0)
   // perror("chdir() to /usr failed");

  // changing the cwd to /tmp
  //if (chdir("/tmp") != 0)
    //perror("chdir() to /temp failed");

  if (chdir(av[1]) != 0)
	  perror(av[1]);

  return 0;
}
*/
/*
#include<unistd.h>
int main()
{
    char s[100];

    // printing current working directory
    printf("%s\n", getcwd(s, 100));

    // using the command
    chdir("..");

    // printing current working directory
    printf("%s\n", getcwd(s, 100));

    // after chdir is executed
    return 0;
}
*/

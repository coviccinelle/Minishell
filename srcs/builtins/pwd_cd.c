#include "../../minishell.h"

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
}

/*
void	exec_cd(int ac, char **av)
{
	int	fd;

	fd = 0;
	if (ac == 1)  // cd sans arg, retourne à la racine, avant desktop
		go_to_pwd_home //même question, comment se déplacer?
	if (ac > 2) // trop d’arg
		ft_puterror_fd(av[0], "string not in pwd: ", av[1]);
	if (ac == 2 && av[1] is_file) // message erreur fichier
		//comme mon solong mais le contraire ?si tu peux owronly dedans n’est pas un dossier?

	fd = open(av[1], O_WRONLY);

	if ((fd != -1) //si pas d’erreur et que tu as réussi à ouvrir**
		ft_puterror_fd("cd: ", "not a directory: ", av[1]);
//success cases and associated errors
	if (ac == 2 && av[2][0] == ‘-’ && av[2][1] == ‘\0’)
		go_to_old_pwd && ret 0
	if (ac == 2 && av[1] est un dossier)
	{
		if (pas trouvé dossier)
			ft_puterror_fd("cd: ", "no such file or directory: ", av[1]);
		else if (trouve dossier)
			//se deplace. à voir comment. 
			// enregistre une sorte de data→old_pwd = com_pwd(), 
			//en effet serait utile pour savoir où atterir exactement pour cd- 
	}
}
*/

int	main(int ac, char **av)
{
	exec_pwd();
	return (0);
}

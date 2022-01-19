#include "../minishell.h"

int exec_pwd(int ac) 
{
	char *pwd;

	pwd = getcwd(NULL, 0); // si sur linux sinon il faut remplacer NULL et 0
	if (ac > 1)
	{
		ft_puterror_fd("pwd: too many arguments", NULL, NULL);
		return (EXIT_FAILURE);
	}
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

int	main(int ac, char **av)
{
	exec_pwd(ac);
	return (0);
}

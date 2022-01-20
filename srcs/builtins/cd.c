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

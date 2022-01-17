//a mettre en define:
//EXIT_FAIL: 126 <= if not executable
//EXIT_SUCCESS: 0
int exec_echo(char **av, int ac)
{
	int j;
	if (option_n == 1) 
		j = 2; // (car av[0] est "echo" et av[1] est "-n")
	else if (option_n == 0) 
		j = 1; //(car av[0] est "echo")
	if(!av[j]&& data→option_n == 1) //peut etre a tej
		return (EXIT_SUCCESS);
	else if(!av[j] && data→option_n == 0)  //peut etre a tej
	{
		ft_putstr_fd(”\n”, 1);
		return (EXIT_SUCCESS);
	}
	while (av[j])
	{
		ft_putstr_fd(av[j], 1);
		if ((j + 1) != ac) // si bug surement ici; tenter j ou ac + 1. nb d'args à enregistrer dans struct
			ft_putchar_fd(' ', 1);
		j++;
	}
	if (data→option_n == 0)
		ft_putstr_fd("\n", 1);
	}
	return (EXIT_SUCCESS);
}

//utils
void    ft_putchar_fd(char c, int fd)
 {
    if (fd < 0)
    	return ;
    write(fd, &c, 1);
  }

void	ft_putstr_fd(char *s, int fd)
{
		if (!(s) || fd < 0)
				return ; //ret -1?
		write(fd, s, ft_strlen(s));
			//ret 0?
}

void    ft_putendl_fd(char *s, int fd)
{
     if (!(s) || fd < 0)
	     return ;
     write(fd, s, ft_strlen(s));
     write(fd, "\n", 1);
 }

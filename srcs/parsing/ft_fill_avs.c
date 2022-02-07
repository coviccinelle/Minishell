


int	ft_paste_av(t_cmd *one_cmd, char **new, char *line)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (one_cmd->avs[y])
	{
		new[y] = malloc(sizeof(char) * (ft_strlen(one_cmd->avs[y]) + 1));
		if (!new[y])
			return (0);
		while (one_cmd->avs[y][i])
		{	
			new[y][i] = one_cmd->avs[y][i];
			i++;
		}
		new[y][i] = '\0';
		i = 0;
		y++;
	}
	new[y] = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new[y])
		return (0);
	ft_strcpy(new[y], line);
	new[++y] = NULL;
	return (1);
}

void	free_avs(char **avs)
{
	int	i;

	i = 0;
	if (avs)
	{
		while (avs[i])
		{
			if (avs[i])
			{
				free(avs[i]);
				avs[i] = NULL;
			}
			i++;
		}
	}
	free(avs);
	avs = NULL;
}

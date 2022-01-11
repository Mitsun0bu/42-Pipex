/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:45:17 by llethuil          #+#    #+#             */
/*   Updated: 2022/01/11 19:47:38 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_files(char **av, t_cmd *cmd)
{
	cmd->fd_1 = open(av[1], O_RDONLY);
	if (cmd->fd_1 < 0)
		error_handler(av, ERR_INFILE);
	cmd->fd_2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd->fd_2 < 0)
		error_handler(av, ERR_OUTFILE);
	return (0);
}

void	get_cmd_names(char **av, t_cmd *cmd)
{
	cmd->name_1 = ft_split(av[2], ' ');
	cmd->name_2 = ft_split(av[3], ' ');
}

void	get_paths_tab(char **envp, t_cmd *cmd)
{
	int		i;
	char	*paths_line;
	char	*buff;

	i = -1;
	paths_line = NULL;
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5) != NULL)
		{
			paths_line = ft_substr(*envp, 5, ft_strlen(*envp));
			break ;
		}
		envp++;
	}
	cmd->paths_tab = ft_split(paths_line, ':');
	while (cmd->paths_tab[++i])
	{
		buff = cmd->paths_tab[i];
		cmd->paths_tab[i] = ft_strjoin(cmd->paths_tab[i], "/");
		free(buff);
	}
	free(paths_line);
}

char	*assign_path(char **av, char *arg, char *cmd_name, t_cmd *cmd)
{
	int		i;
	char	*path;

	i = -1;
	while (cmd->paths_tab[++i])
	{
		if (access(arg, F_OK) == 0)
			return (arg);
		path = ft_strjoin(cmd->paths_tab[i], cmd_name);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		path = NULL;
	}
	if (access(path, F_OK) == -1 && cmd_name == cmd->name_1[0])
		error_handler(av, ERR_CMD_1);
	if (access(path, F_OK) == -1 && cmd_name == cmd->name_2[0])
		error_handler(av, ERR_CMD_2);
	return (NULL);
}

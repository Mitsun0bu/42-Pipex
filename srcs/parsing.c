/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:45:17 by llethuil          #+#    #+#             */
/*   Updated: 2022/01/11 16:48:32 by llethuil         ###   ########lyon.fr   */
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

void	assign_path(char **av, t_cmd *cmd)
{
	int		i;

	i = -1;
	while (cmd->paths_tab[++i])
	{
		cmd->path_1 = ft_strjoin(cmd->paths_tab[i], cmd->name_1[0]);
		if (access(cmd->path_1, F_OK) == 0)
			break ;
		free(cmd->path_1);
		cmd->path_1 = NULL;
	}
	if (access(cmd->path_1, F_OK) == -1)
		error_handler(av, ERR_CMD_1);
	i = -1;
	while (cmd->paths_tab[++i])
	{
		cmd->path_2 = ft_strjoin(cmd->paths_tab[i], cmd->name_2[0]);
		if (access(cmd->path_2, F_OK) == 0)
			break ;
		free(cmd->path_2);
		cmd->path_2 = NULL;
	}
	if (access(cmd->path_2, F_OK) == -1)
		error_handler(av, ERR_CMD_2);
}

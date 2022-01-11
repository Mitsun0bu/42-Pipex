/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 11:56:56 by llethuil          #+#    #+#             */
/*   Updated: 2022/01/11 19:45:59 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_cmd	cmd;

	ft_memset(&cmd, 0, sizeof(cmd));
	if (ac != 5)
	{
		error_handler(av, ERR_INPUT);
		exit (1);
	}
	if (open_files(av, &cmd) == -1)
		exit (1);
	get_cmd_names(av, &cmd);
	get_paths_tab(envp, &cmd);
	cmd.path_1 = assign_path(av, av[2], cmd.name_1[0], &cmd);
	cmd.path_2 = assign_path(av, av[3], cmd.name_2[0], &cmd);
	pipex(envp, &cmd);
	free_cmd(av, &cmd);
	return (0);
}

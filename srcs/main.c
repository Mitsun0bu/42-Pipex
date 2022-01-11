/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 11:56:56 by llethuil          #+#    #+#             */
/*   Updated: 2022/01/11 16:13:37 by llethuil         ###   ########lyon.fr   */
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
	assign_path(av, &cmd);
	pipex(envp, &cmd);
	free_cmd(&cmd);
	return (0);
}

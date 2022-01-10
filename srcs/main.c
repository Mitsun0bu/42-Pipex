/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 11:56:56 by llethuil          #+#    #+#             */
/*   Updated: 2022/01/10 20:05:12 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*

./pipex file1 cmd1 cmd2 file2

*/

int	main(int ac, char **av, char **envp)
{
	t_cmd	cmd;
	int		i;

	ft_memset(&cmd, 0, sizeof(cmd));
	open_files(ac, av, &cmd);
	get_paths_tab(envp, &cmd);
	i = -1;
	while (cmd.paths_tab[++i])
		printf("cmd.paths_tab[%d] = %s\n", i, cmd.paths_tab[i]);
	assign_path(av, &cmd);
	printf("cmd.path_1 = %s\n", cmd.path_1);
	printf("cmd.path_2 = %s\n", cmd.path_2);
	// // pipex(&cmd);
	free(cmd.path_1);
	free(cmd.path_2);
	ft_free(cmd.paths_tab);
	return (0);
}

int	open_files(int ac, char **av, t_cmd *cmd)
{
	(void)ac;
	cmd->fd_1 = open(av[1], O_RDONLY);
	if (!cmd->fd_1)
	{
		ft_putstr_fd(av[1], 1);
		ft_putstr_fd(": No such file or directory\n", 1);
	}
	cmd->fd_2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd->fd_1 < 0 || cmd->fd_2 < 0)
		return (-1);
	return (0);
}

void	get_paths_tab(char **envp, t_cmd *cmd)
{
	int		i;
	char	*paths_line;

	i = -1;
	paths_line = NULL;
	while(*envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5) != NULL)
		{
			paths_line = ft_substr(*envp, 5, ft_strlen(*envp));
			break;
		}
		envp++;
	}
	cmd->paths_tab = ft_split(paths_line, ':');
	// while(cmd->paths_tab[++i])
	// 	cmd->paths_tab[i] = ft_strjoin(cmd->paths_tab[i], "/");
	free(paths_line);
}

void assign_path(char **av, t_cmd *cmd)
{
	int		i;

	i = -1;
	while (cmd->paths_tab[++i])
	{
		cmd->path_1 = ft_strjoin(cmd->paths_tab[i], av[2]);
		if (access(cmd->paths_tab[i], X_OK) == 0)
			break;
		i++;
	}
	i = -1;
	while (cmd->paths_tab[++i])
	{
		cmd->path_2 = ft_strjoin(cmd->paths_tab[i], av[3]);
		if (access(cmd->paths_tab[i], X_OK) == 0)
			break;
		i++;
	}
	return ;
}

// void	pipex(t_cmd *cmd)
// {
// 	int		pipe_end_fd[2];
// 	int		status;
// 	pid_t	task_1;
// 	pid_t	task_2;
// 	pipe(pipe_end_fd);
// 	task_1 = fork();
// 	if (task_1 < 0)
// 	     return (perror("Fork: "));
// 	if (task_1 == 0)
// 	{
// 		task_process(cmd);
// 		waitpid(task_1, &status, 0);
// 	}
// 	task_2 = fork();
// 	if (task_2 < 0)
// 	     return (perror("Fork: "));
// 	if (task_2 == 0)
// 	{
// 		task_process(cmd);
// 		waitpid(task_2, &status, 0);
// 	}
// 	close(pipe_end_fd[0]);
// 	close(pipe_end_fd[1]);
// }
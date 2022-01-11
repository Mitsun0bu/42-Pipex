/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 11:56:56 by llethuil          #+#    #+#             */
/*   Updated: 2022/01/11 12:25:26 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*

./pipex file1 cmd1 cmd2 file2

*/

int	main(int ac, char **av, char **envp)
{
	t_cmd	cmd;

	ft_memset(&cmd, 0, sizeof(cmd));
	if (ac != 5)
		exit (0);
	if (open_files(av, &cmd) == -1)
		exit (0);
	get_cmd_names(av, &cmd);
	get_paths_tab(envp, &cmd);
	assign_path(&cmd);
	pipex(envp, &cmd);
	free_cmd_end(&cmd);
	return (0);
}

int	open_files(char **av, t_cmd *cmd)
{
	cmd->fd_1 = open(av[1], O_RDONLY);
	if (cmd->fd_1 < 0)
		error_handler(av, ERR_INFILE);
	cmd->fd_2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd->fd_2 < 0)
		return (-1);
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
	while(cmd->paths_tab[++i])
	{
		buff = cmd->paths_tab[i];
		cmd->paths_tab[i] = ft_strjoin(cmd->paths_tab[i], "/");
		free(buff);
	}
	free(paths_line);
}

void	assign_path(t_cmd *cmd)
{
	int		i;

	i = -1;
	while (cmd->paths_tab[++i])
	{
		cmd->path_1 = ft_strjoin(cmd->paths_tab[i], cmd->name_1[0]);
		if (access(cmd->path_1, F_OK) == 0)
			break;
		free(cmd->path_1);
	}
	i = -1;
	while (cmd->paths_tab[++i])
	{
		cmd->path_2 = ft_strjoin(cmd->paths_tab[i], cmd->name_2[0]);
		if (access(cmd->path_2, F_OK) == 0)
			break;
		free(cmd->path_2);
	}
}

void	pipex(char **envp, t_cmd *cmd)
{
	int		pipe_fd[2];
	int		status;
	pid_t	task_1;
	pid_t	task_2;

	if (pipe(pipe_fd) == -1)
		exit(0);
	task_1 = fork();
	if (task_1 < 0)
	     return (perror("Fork: "));
	if (task_1 == 0)
		task_process(1, pipe_fd, cmd, envp);
	task_2 = fork();
	if (task_2 < 0)
	     return (perror("Fork: "));
	if (task_2 == 0)
		task_process(2, pipe_fd, cmd, envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(task_1, &status, 0);
	waitpid(task_2, &status, 0);
}

void	task_process(int i, int *pipe_fd, t_cmd *cmd, char **envp)
{
	if (i == 1)
	{
		dup2(cmd->fd_1, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(cmd->fd_1);
		execve(cmd->path_1, cmd->name_1, envp);
	}
	if (i == 2)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(cmd->fd_2, STDOUT_FILENO);
		close(pipe_fd[1]);
		close(cmd->fd_2);
		execve(cmd->path_2, cmd->name_2, envp);
	}
	// EXIT FAILURE ?
}

void	error_handler(char **av, char *err)
{
	if(err == ERR_INFILE)
		perror(av[1]);
	exit (0);
}

void	free_cmd_end(t_cmd *cmd)
{
	ft_free(cmd->paths_tab);
	ft_free(cmd->name_1);
	ft_free(cmd->name_2);
	free(cmd->path_1);
	free(cmd->path_2);
}
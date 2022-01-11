/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:44:38 by llethuil          #+#    #+#             */
/*   Updated: 2022/01/11 19:11:40 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	pipex(char **envp, t_cmd *cmd)
{
	int		pipe_fd[2];
	int		status;
	pid_t	task_1;
	pid_t	task_2;

	if (pipe(pipe_fd) == -1)
		error_handler(NULL, ERR_PIPE);
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

void	task_process(int x, int *pipe_fd, t_cmd *cmd, char **envp)
{
	if (x == 1)
	{
		dup2(cmd->fd_1, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(cmd->fd_1);
		if (cmd->path_1)
			execve(cmd->path_1, cmd->name_1, envp);
		exit(EXIT_FAILURE);
	}
	if (x == 2)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(cmd->fd_2, STDOUT_FILENO);
		close(pipe_fd[1]);
		close(cmd->fd_2);
		if (cmd->path_2)
			execve(cmd->path_2, cmd->name_2, envp);
		exit(EXIT_FAILURE);
	}
}

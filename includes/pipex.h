/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 11:54:29 by llethuil          #+#    #+#             */
/*   Updated: 2022/01/12 12:26:43 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                               ~~~ DEFINES ~~~                              */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define ERR_INFILE "infile"
# define ERR_OUTFILE "outfile"
# define ERR_INPUT "n_args"
# define ERR_CMD_1 "cmd_1"
# define ERR_CMD_2 "cmd_2"
# define ERR_PIPE "pipe"
# define ERR_FORK "fork"

/* ************************************************************************** */
/*                                                                            */
/*                               ~~~ INCLUDES ~~~                             */
/*                                                                            */
/* ************************************************************************** */

/* access, close, dup2, execve, fork, pipe, read, write */
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

/* exit, free, malloc */
# include <stdlib.h>

/* open */
# include <fcntl.h>

/* perror */
# include <stdio.h>

/* waitpid */
# include <sys/wait.h>

/* ************************************************************************** */
/*                                                                            */
/*                              ~~~ TYPEDEFS ~~~                              */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_cmd
{
	int		fd_1;
	int		fd_2;
	char	**paths_tab;
	char	**name_1;
	char	**name_2;
	char	*path_1;
	char	*path_2;
}	t_cmd;

/* ************************************************************************** */
/*                                                                            */
/*                              ~~~ PROTOTYPES ~~~                            */
/*                                                                            */
/* ************************************************************************** */

/* main.c */
int		main(int ac, char **av, char **envp);

/* parsing.c */
int		open_files(char **av, t_cmd *cmd);
void	get_cmd_names(char **av, t_cmd *cmd);
void	get_paths_tab(char **envp, t_cmd *cmd);
char	*assign_path(char **av, char *arg, char *cmd_name, t_cmd *cmd);

/* pipex.c */
int		pipex(char **envp, t_cmd *cmd);
void	task_process(int x, int *pipe_fd, t_cmd *cmd, char **envp);

/* utils_1.c */
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *str);

/* utils_2.c */
char	**ft_split(char const *s, char c);
int		ft_count_words(char const *s, char c);
void	ft_free(char **tab);
int		ft_calloc_strs(char const *s, char c, char **tab);
void	ft_fill_tab(char const *s, char c, char **tab);

/* utils_3.c */
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	error_handler(char **av, char *err);
void	free_cmd(char **av, t_cmd *cmd);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 11:54:29 by llethuil          #+#    #+#             */
/*   Updated: 2022/01/10 20:05:19 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                               ~~~ DEFINES ~~~                              */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* ************************************************************************** */
/*                                                                            */
/*                               ~~~ INCLUDES ~~~                             */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>

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
	char	*name_1;
	char	*name_2;
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
int		open_files(int ac, char **av, t_cmd *cmd);
void	get_paths_tab(char **envp, t_cmd *cmd);
void	assign_path(char **av, t_cmd *cmd);
void	pipex(t_cmd *cmd);

/* utils_1.c */
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *str);

// /* ft_split.c */
// char	**ft_split(char const *s, char c);
// int		ft_count_words(char const *s, char c);
// void	ft_free(char **tab);
// int		ft_calloc_strs(char const *s, char c, char **tab);
// void	ft_fill_tab(char const *s, char c, char **tab);

/* utils_2.c */
char	**ft_split(char const *s, char c);
int		ft_count_words(char const *s, char c);
void		ft_free(char **tab);
int		ft_calloc_strs(char const *s, char c, char **tab);
void	ft_fill_tab(char const *s, char c, char **tab);

/* utils_3.c */
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:12:14 by abaldelo          #+#    #+#             */
/*   Updated: 2025/01/27 21:41:43 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>

void	execute_cmd1(int infile, int pipe_fd[2], char *cmd1, char **envp);
void	execute_cmd2(int outfile, int pipe_fd[2], char *cmd2, char **envp);
void	call_forks(int files[2], int pipe_fd[2], char **argv, char **envp);
void	error_exit(const char *msg);
void	close_fds(int fd1, int fd2, int fd3, int fd4);
void	ft_putstr_stderr(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		path_in_envp(char **envp);

#endif
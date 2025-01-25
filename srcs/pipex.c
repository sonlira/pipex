/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:11:41 by abaldelo          #+#    #+#             */
/*   Updated: 2025/01/25 21:04:43 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_in_child(int infile, int pipe_fd[2], char *cmd1, char **envp)
{
	char	*args[4];

	if (dup2(infile, STDIN_FILENO) == -1)
		error_exit("dup2 infile error");
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		error_exit("dup2 pipe write error");
	close_fds(pipe_fd[0], pipe_fd[1], infile, -1);
	args[0] = "/bin/sh";
	args[1] = "-c";
	args[2] = cmd1;
	args[3] = NULL;
	if (execve(args[0], args, envp) == -1)
		error_exit("execve cmd1 error");
}

void	execute_in_father(int outfile, int pipe_fd[2], char *cmd2, char **envp)
{
	char	*args[4];

	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		error_exit("dup2 pipe read error");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		error_exit("dup2 outfile error");
	close_fds(pipe_fd[0], pipe_fd[1], outfile, -1);
	args[0] = "/bin/sh";
	args[1] = "-c";
	args[2] = cmd2;
	args[3] = NULL;
	if (execve(args[0], args, envp) == -1)
		error_exit("execve cmd2 error");
}

void	call_forks(int files[2], int pipe_fd[2], char **argv, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit("Fork error");
	if (pid == 0)
		execute_in_child(files[0], pipe_fd, argv[2], envp);
	execute_in_father(files[1], pipe_fd, argv[3], envp);
	close_fds(pipe_fd[0], pipe_fd[1], files[0], files[1]);
	waitpid(pid, NULL, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:11:44 by abaldelo          #+#    #+#             */
/*   Updated: 2025/01/25 21:02:28 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		files[2];

	if (argc != 5)
	{
		write(2, "Usage: ./pipex file1 \"cmd1\" \"cmd2\" file2\n", 42);
		return (EXIT_FAILURE);
	}
	files[0] = open(argv[1], O_RDONLY);
	if (files[0] < 0)
		error_exit("Error opening infile");
	files[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (files[1] < 0)
		error_exit("Error opening outfile");
	if (pipe(pipe_fd) == -1)
		error_exit("Pipe error");
	call_forks(files, pipe_fd, argv, envp);
	return (EXIT_SUCCESS);
}

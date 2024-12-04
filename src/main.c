/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:30:36 by cgrasser          #+#    #+#             */
/*   Updated: 2024/12/04 11:20:58 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void	exit_error(void)
{
	perror("Error\n");
	exit(EXIT_FAILURE);
}

void	child_process(char **argv, char **envp, int *fd)
{
	int	fd_finput;

	fd_finput = open(argv[1], O_RDONLY, 0777);
	if (fd_finput == -1)
		exit_error();
}

void	parent_process(char **argv, char **envp, int *fd)
{
	
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
	{
		ft_putendl_fd("Error: Bad arguments", 2);
		ft_putendl_fd("Usage: ./pipex <file1> <cmd1> <cmd2> <file2>", 1);
		return (1);
	}
	if (pipe(fd) == -1)
		exit_error();
	pid = fork();
	if (pid == 0)
		child_process();
	waitpid(pid, NULL, 0);
	parent_process();
	return (0);
}


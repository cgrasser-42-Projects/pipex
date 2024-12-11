/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:44:52 by cgrasser          #+#    #+#             */
/*   Updated: 2024/12/11 10:25:23 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		exit_error("Error : Command path not found");
	}
	if (execve(path, cmd, envp) == -1)
		exit_error("Error : Execute command");
}

static void	pipe_process(char *cmd, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit_error("Error : fd -> pipe()");
	pid = fork();
	if (pid == -1)
		exit_error("Error : pid -> fork()");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(cmd, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

static void	here_doc(char *limiter, int argc)
{
	pid_t	reader;
	int		fd[2];

	if (argc < 6)
		usage();
	if (pipe(fd) == -1)
		exit_error("Error : fd -> pipe()");
	reader = fork();
	if (reader == 0)
		read_stdin(fd, limiter);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	filein;
	int	fileout;

	if (argc < 5)
		usage();
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		here_doc(argv[2], argc);
	}
	else
	{
		i = 2;
		fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		filein = open(argv[1], O_RDONLY, 0777);
		dup2(filein, STDIN_FILENO);
	}
	while (i < argc - 2)
		pipe_process(argv[i++], envp);
	dup2(fileout, STDOUT_FILENO);
	execute(argv[argc - 2], envp);
	return (0);
}

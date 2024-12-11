/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:10:43 by cgrasser          #+#    #+#             */
/*   Updated: 2024/12/11 10:19:16 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}

void	usage(void)
{
	ft_printf("Error :\nUsage : %s\n", USAGE);
	ft_printf("%59s\n", USAGE_HERE_DOC);
	exit(EXIT_FAILURE);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	return (free(paths), NULL);
}

void	read_stdin(int *fd, char *limiter)
{
	char	*line;

	close(fd[0]);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	exit(EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:01:01 by cgrasser          #+#    #+#             */
/*   Updated: 2024/12/11 10:01:27 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"

# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

# define USAGE "./pipex <file1> <cmd> <cmd> <...> <file2>"
# define USAGE_HERE_DOC "./pipex here_doc <LIMITER> <cmd> <cmd> <...> <file>"

//=====================================================================| UTILS |

void	exit_error(char *error_msg);
void	usage(void);
char	*find_path(char *cmd, char **envp);
void	read_stdin(int *fd, char *limiter);

#endif

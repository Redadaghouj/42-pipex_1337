/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:40:27 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/26 01:12:36 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_t_pipex(char **argv, int argc, t_pipex *pipex)
{
	pipex->cmd = NULL;
	pipex->args = NULL;
	pipex->full_path = NULL;
	pipex->cmd_paths = NULL;
	pipex->path = NULL;
	pipex->argv = argv + 1;
	pipex->slash = 0;
	pipex->count = argc - 2;
	pipex->heredoc = -1;
}

int	check_file_permission(t_pipex *pipex, char *infile, char *outfile)
{
	int	flag;

	flag = 0;
	pipex->infile_fd = open(infile, O_RDONLY);
	pipex->outfile_fd = open(outfile, O_WRONLY | O_CREAT
			| O_TRUNC, 0666);
	if (pipex->infile_fd < 0)
	{
		flag = -1;
		perror("Error");
	}
	if (pipex->outfile_fd < 0)
	{
		flag = -1;
		perror("Error");
	}
	return (flag);
}

int	dup3(int old_fd, int new_fd)
{
	int	fd;

	fd = dup2(old_fd, new_fd);
	if (fd >= 0)
		close(old_fd);
	return (fd);
}

int	ft_fork(t_pipex *pipex)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		safe_exit(pipex, 1);
	return (pid);
}

void	parent_cleanup(int *prev_fd, int count, int pipefd[], int i)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (i < count - 1)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:40:27 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/26 05:33:50 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_infile_permission(t_pipex *pipex)
{
	pipex->infile_fd = open(pipex->infile, O_RDONLY);
	if (pipex->infile_fd < 0)
		perror("pipex");
}

void	check_outfile_permission(t_pipex *pipex, int pipefd[])
{
	pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT
			| O_TRUNC, 0666);
	if (pipex->outfile_fd < 0)
	{
		close(pipefd[0]);
		safe_exit(pipex, 1);
	}
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

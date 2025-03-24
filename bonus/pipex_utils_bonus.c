/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:40:27 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/24 06:51:37 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_t_pipex(char **argv, int argc, t_pipex *pipex)
{
	pipex->infile = argv[0];
	pipex->cmd = NULL;
	pipex->outfile = argv[(argc - 1)];
	pipex->args = NULL;
	pipex->cmd_paths = NULL;
	pipex->path = NULL;
	pipex->argv = argv + 1;
	pipex->slash = 0;
	pipex->count = argc - 2;
}

int	check_file_permission(t_pipex *pipex)
{
	int	flag;

	flag = 0;
	pipex->infile_fd = open(pipex->infile, O_RDONLY);
	pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->infile_fd < 0)
	{
		flag = -1;
		print_error(strerror(errno), pipex->infile);
	}
	if (pipex->outfile_fd < 0)
	{
		flag = -1;
		print_error(strerror(errno), pipex->outfile);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:40:27 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/22 21:51:12 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_t_pipex(char **argv, t_pipex *pipex)
{
	pipex->infile = argv[0];
	pipex->cmd1 = argv[1];
	pipex->cmd2 = argv[2];
	pipex->outfile = argv[3];
}

int	check_file_permission(t_pipex *pipex)
{
	int	flag;

	flag = 0;
	pipex->infile_fd = open(pipex->infile, O_RDONLY);
	pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
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

int	ft_fork(t_pipex *pipex, char **cmd_path)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		safe_exit(pipex, cmd_path);
	return (pid);
}

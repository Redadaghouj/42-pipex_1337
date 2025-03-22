/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:40:27 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/22 03:49:07 by mdaghouj         ###   ########.fr       */
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

int	check_infile_permission(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error(strerror(errno), file);
	return (fd);
}

int	check_outfile_permission(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT);
	if (fd < 0)
		print_error(strerror(errno), file);
	return (fd);
}

int	dup3(int old_fd, int new_fd)
{
	int	fd;
	fd = dup2(old_fd, new_fd);
	if (fd >= 0)
		close(old_fd);
	return (fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:26:08 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/23 02:25:46 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *msg, char *file)
{
	ft_putstr("pipex: ");
	ft_putstr(msg);
	ft_putstr(": ");
	ft_putstr(file);
	ft_putstr("\n");
}

void	safe_exit(t_pipex *pipex, int err)
{
	if (pipex->infile_fd >= 0)
		close(pipex->infile_fd);
	if (pipex->outfile_fd >= 0)
		close(pipex->outfile_fd);
	free_buffer(pipex->cmd_paths);
	free_buffer(pipex->args1);
	free_buffer(pipex->args2);
	if (err)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

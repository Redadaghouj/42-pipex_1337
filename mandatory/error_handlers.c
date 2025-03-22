/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:26:08 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/22 21:46:22 by mdaghouj         ###   ########.fr       */
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

void	safe_exit(t_pipex *pipex, char **cmd_path)
{
	if (pipex->infile_fd >= 0)
		close(pipex->infile_fd);
	if (pipex->outfile_fd >= 0)
		close(pipex->outfile_fd);
	free_buffer(cmd_path);
	perror("Error");
	exit(EXIT_FAILURE);
}
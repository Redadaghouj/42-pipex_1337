/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:26:08 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/26 01:13:10 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	safe_exit(t_pipex *pipex, int err)
{
	if (err)
		perror("Error");
	if (pipex->infile_fd >= 0)
		close(pipex->infile_fd);
	if (pipex->outfile_fd >= 0)
		close(pipex->outfile_fd);
	free_buffer(pipex->cmd_paths);
	free_buffer(pipex->args);
	free_buffer(pipex->full_path);
	if (err)
		exit(EXIT_FAILURE);
}

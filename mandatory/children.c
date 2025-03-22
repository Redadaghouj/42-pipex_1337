/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:30:30 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/22 21:48:48 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipex *pipex, int pipefd[], char **cmd_paths)
{
	int		i;
	char	*path;

	i = 0;
	close(pipefd[0]);
	dup3(pipex->infile_fd, STDIN_FILENO);
	dup3(pipefd[1], STDOUT_FILENO);
	while (cmd_paths[i] != NULL)
	{
		path = ft_strjoin(cmd_paths[i], pipex->cmd1);
		execv(path, ft_split(pipex->cmd1, ' '));
		free(path);
		i++;
	}
	safe_exit(pipex, cmd_paths);
}

void	second_child(t_pipex *pipex, int pipefd[], char **cmd_paths)
{
	int		i;
	char	*path;

	i = 0;
	close(pipefd[1]);
	dup3(pipefd[0], STDIN_FILENO);
	dup3(pipex->outfile_fd, STDOUT_FILENO);
	while (cmd_paths[i] != NULL)
	{
		path = ft_strjoin(cmd_paths[i], pipex->cmd2);
		execv(path, ft_split(pipex->cmd2, ' '));
		free(path);
		i++;
	}
	safe_exit(pipex, cmd_paths);
}

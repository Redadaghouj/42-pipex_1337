/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:30:30 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/25 07:42:19 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	setup_child_process(t_pipex *pipex, int i, int pipefd[], int prev_fd)
{
	if (i == 0)
	{
		dup3(pipefd[1], STDOUT_FILENO);
		dup3(pipex->infile_fd, STDIN_FILENO);
	}
	else if (i < pipex->count - 1)
	{
		dup3(prev_fd, STDIN_FILENO);
		dup3(pipefd[1], STDOUT_FILENO);
	}
	else
	{
		close(pipefd[1]);
		dup3(prev_fd, STDIN_FILENO);
		dup3(pipex->outfile_fd, STDOUT_FILENO);
	}
	close(pipefd[0]);
}

void	execute_child(t_pipex *pipex, char *envp[])
{
	int		i;
	char	**x;

	i = 0;
	if (pipex->slash || *envp == NULL)
	{
		execve(pipex->full_path[0], pipex->args, envp);
		safe_exit(pipex, 1);
	}
	else
	{
		while (pipex->cmd_paths[i] != NULL)
		{
			x = ft_split(pipex->cmd, ' ');
			pipex->path = ft_strjoin(pipex->cmd_paths[i], x[0]);
			execve(pipex->path, pipex->args, envp);
			free(pipex->path);
			free_buffer(x);
			i++;
		}
	}
	safe_exit(pipex, 1);
}

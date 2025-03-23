/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:30:30 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/23 03:54:43 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipex *pipex, int pipefd[], char *envp[])
{
	int	i;

	i = 0;
	close(pipefd[0]);
	dup3(pipefd[1], STDOUT_FILENO);
	dup3(pipex->infile_fd, STDIN_FILENO);
	if (pipex->cmd1[0] == '/')
	{
		pipex->args1 = ft_split(pipex->cmd1 + 1, ' ');
		execve(pipex->cmd1, pipex->args1, envp);
		safe_exit(pipex, 1);
	}
	else
		pipex->args1 = ft_split(pipex->cmd1, ' ');
	while (pipex->cmd_paths[i] != NULL)
	{
		pipex->path = ft_strjoin(pipex->cmd_paths[i], pipex->cmd1);
		execve(pipex->path, pipex->args1, envp);
		free(pipex->path);
		i++;
	}
	safe_exit(pipex, 1);
}

void	second_child(t_pipex *pipex, int pipefd[], char *envp[])
{
	int	i;

	i = 0;
	close(pipefd[1]);
	dup3(pipefd[0], STDIN_FILENO);
	dup3(pipex->outfile_fd, STDOUT_FILENO);
	if (pipex->cmd2[0] == '/') // cmd = ls -e handle
	{
		pipex->args2 = ft_split(pipex->cmd2 + 1, ' ');
		execve(pipex->cmd2, pipex->args2, envp);
		safe_exit(pipex, 1);
	}
	else
		pipex->args2 = ft_split(pipex->cmd2, ' ');
	i=0;
	while (pipex->cmd_paths[i] != NULL)
	{
		pipex->path = ft_strjoin(pipex->cmd_paths[i], pipex->cmd2);
		execve(pipex->path, pipex->args2, envp);
		free(pipex->path);
		i++;
	}
	safe_exit(pipex, 1);
}

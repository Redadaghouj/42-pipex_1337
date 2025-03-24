/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:30:30 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/24 05:18:33 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipex *pipex, int pipefd[], char *envp[])
{
	int		i;
	char	**x;

	i = 0;
	close(pipefd[0]);
	dup3(pipefd[1], STDOUT_FILENO);
	dup3(pipex->infile_fd, STDIN_FILENO);
	if (pipex->slash1 || *envp == NULL)
	{
		execve(pipex->argv[0], pipex->args1, envp);
		safe_exit(pipex, 1);
	}
	else
	{
		while (pipex->cmd_paths[i] != NULL)
		{
			x = ft_split(pipex->cmd1, ' ');
			pipex->path = ft_strjoin(pipex->cmd_paths[i], x[0]);
			execve(pipex->path, pipex->args1, envp);
			free(pipex->path);
			free_buffer(x);
			i++;
		}
	}
	safe_exit(pipex, 1);
}

void	second_child(t_pipex *pipex, int pipefd[], char *envp[])
{
	int		i;
	char	**x;

	i = 0;
	close(pipefd[1]);
	dup3(pipefd[0], STDIN_FILENO);
	dup3(pipex->outfile_fd, STDOUT_FILENO);
	if (pipex->slash2 || *envp == NULL)
	{
		x = ft_split(pipex->argv[1], ' ');
		execve(x[0], pipex->args2, envp);
		free_buffer(x);
		safe_exit(pipex, 1);
	}
	else
	{
		while (pipex->cmd_paths[i] != NULL)
		{
			x = ft_split(pipex->cmd2, ' ');
			pipex->path = ft_strjoin(pipex->cmd_paths[i], x[0]);
			execve(pipex->path, pipex->args2, envp);
			free(pipex->path);
			free_buffer(x);
			i++;
		}
	}
	safe_exit(pipex, 1);
}

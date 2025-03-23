/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:30:30 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/23 05:46:27 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	print2(t_pipex *pipex)
// {
// 	int i=0;
// 	ft_putstr(pipex->cmd1);
// 	ft_putstr("\n");
// 	while (pipex->args1[i] != NULL)
// 	{
// 		ft_putstr(pipex->args1[i]);
// 		ft_putstr(" ");
// 		i++;
// 	}
// 	ft_putstr("\n");
// }

void	first_child(t_pipex *pipex, int pipefd[], char *envp[])
{
	int	i;
	char	**x;

	i = 0;
	close(pipefd[0]);
	dup3(pipefd[1], STDOUT_FILENO);
	dup3(pipex->infile_fd, STDIN_FILENO);
	if (pipex->cmd1[0] == '/')
	{
		x = ft_split(pipex->cmd1, ' ');
		execve(x[0], pipex->args1, envp);
		safe_exit(pipex, 1);
	}
	while (pipex->cmd_paths[i] != NULL)
	{
		x = ft_split(pipex->cmd1 + 1, ' ');
		pipex->path = ft_strjoin(pipex->cmd_paths[i], x[0]);
		execve(pipex->path, pipex->args1, envp);
		free(pipex->path);
		i++;
	}
	safe_exit(pipex, 1);
}

// void	print(t_pipex *pipex)
// {
// 	int i=0;
// 	ft_putstr(pipex->cmd2);
// 	ft_putstr("\n");
// 	while (pipex->args2[i] != NULL)
// 	{
// 		ft_putstr(pipex->args2[i]);
// 		ft_putstr(" ");
// 		i++;
// 	}
// 	ft_putstr("\n");
// }

void	second_child(t_pipex *pipex, int pipefd[], char *envp[])
{
	int	i;
	char	**x;

	i = 0;
	close(pipefd[1]);
	dup3(pipefd[0], STDIN_FILENO);
	dup3(pipex->outfile_fd, STDOUT_FILENO);
	if (pipex->cmd2[0] == '/')
	{
		x = ft_split(pipex->cmd2 + 1, ' ');
		execve(x[0], pipex->args2, envp);
		safe_exit(pipex, 1);
	}
	while (pipex->cmd_paths[i] != NULL)
	{
		x = ft_split(pipex->cmd2, ' ');
		pipex->path = ft_strjoin(pipex->cmd_paths[i], x[0]);
		execve(pipex->path, pipex->args2, envp);
		free(pipex->path);
		i++;
	}
	safe_exit(pipex, 1);
}

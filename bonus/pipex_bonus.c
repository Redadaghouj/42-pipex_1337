/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:19:13 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/24 07:21:05 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	run_pipex(t_pipex *pipex, char *envp[])
{
	int	pipefd[2];
	int	i;

	i = 0;
	if (pipe(pipefd) == -1)
		return ;
	if (ft_fork(pipex) == 0)
	{
		get_args(pipex, i++);
		close(pipefd[0]);
		dup3(pipefd[1], STDOUT_FILENO);
		dup3(pipex->infile_fd, STDIN_FILENO);
		ft_putstr("first cmd\n");
		child_process(pipex, envp);
	}
	while (i < pipex->count)
	{
		get_args(pipex, i++);
		if (ft_fork(pipex) == 0)
		{
			if (i < pipex->count - 1)
			{
				ft_putstr("middles cmd\n");
				dup3(pipefd[0], STDIN_FILENO);
				dup3(pipefd[1], STDOUT_FILENO);
				child_process(pipex, envp);	
			}
			else if (i == pipex->count - 1)
			{
				ft_putstr("last cmd\n");
				close(pipefd[1]);
				dup3(pipefd[0], STDIN_FILENO);
				dup3(pipex->outfile_fd, STDOUT_FILENO);
				child_process(pipex, envp);	
			}
		}
	}
	close(pipefd[0]);
	close(pipefd[1]);
	while (wait(NULL) != -1);
}

void	get_cmd_paths(char *envp[], t_pipex *pipex)
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strstr(envp[i], "PATH") != NULL)
		{
			pipex->cmd_paths = ft_split(&envp[i][5], ':');
			break;
		}
		i++;
	}
}

void	get_args(t_pipex *pipex, int i)
{
	pipex->cmd = pipex->argv[i + 1];
	pipex->cmd = ft_strrchr(pipex->cmd, '/', &pipex->slash);
	pipex->args = ft_split(pipex->cmd, ' ');
	pipex->full_arg = pipex->argv[i + 1];
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc < 5)
		return (EXIT_FAILURE);
	init_t_pipex(argv + 1, argc - 1, &pipex);
	if (check_file_permission(&pipex) < 0)
		return(EXIT_FAILURE);
	get_cmd_paths(envp, &pipex);
	run_pipex(&pipex, envp);
	safe_exit(&pipex, 0);
	return (EXIT_SUCCESS);
}

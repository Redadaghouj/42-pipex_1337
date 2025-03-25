/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda <reda@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:19:13 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/25 20:42:30 by reda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	run_pipex(t_pipex *pipex, char *envp[])
{
	int	pipefd[2];
	int	i;
	int	prev_fd;

	i = 0;
	prev_fd = -1;
	while (i < pipex->count)
	{
		if (i < pipex->count - 1 && pipe(pipefd) == -1)
			return ;
		if (ft_fork(pipex) == 0)
		{
			setup_child_process(pipex, i, pipefd, prev_fd);
			get_args(pipex, i);
			execute_child(pipex, envp);
		}
		parent_cleanup(&prev_fd, pipex->count, pipefd, i);
		i++;
	}
	while (wait(NULL) != -1)
		;
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
			break ;
		}
		i++;
	}
}

void	get_args(t_pipex *pipex, int i)
{
	pipex->cmd = pipex->argv[i];
	pipex->cmd = ft_strrchr(pipex->cmd, '/', &pipex->slash);
	pipex->args = ft_split(pipex->cmd, ' ');
	pipex->full_path = ft_split(pipex->argv[i], ' ');
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc == 6 && ft_strcmp(argv[1], "here_doc") == 0)
		run_here_doc(argv[2]);
	else if (argc < 5)
		return (EXIT_FAILURE);
	init_t_pipex(argv + 1, argc - 1, &pipex);
	if (check_file_permission(&pipex) < 0)
		return (EXIT_FAILURE);
	get_cmd_paths(envp, &pipex);
	run_pipex(&pipex, envp);
	safe_exit(&pipex, 0);
	return (EXIT_SUCCESS);
}

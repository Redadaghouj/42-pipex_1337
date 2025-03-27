/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:19:13 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/26 05:35:53 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_t_pipex(char **argv, int argc, t_pipex *pipex)
{
	pipex->cmd = NULL;
	pipex->args = NULL;
	pipex->full_path = NULL;
	pipex->cmd_paths = NULL;
	pipex->path = NULL;
	pipex->argv = argv + 1;
	pipex->slash = 0;
	pipex->count = argc - 2;
	pipex->infile = argv[0];
	pipex->outfile = argv[(argc - 1)];
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
}

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
			get_args(pipex, i);
			setup_child_process(pipex, i, pipefd, prev_fd);
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

	if (argc != 5)
	{
		ft_putstr("Usage: ./pipex infile cmd1 cmd2 outfile\n");
		return (EXIT_FAILURE);
	}
	init_t_pipex(argv + 1, argc - 1, &pipex);
	check_infile_permission(&pipex);
	get_cmd_paths(envp, &pipex);
	run_pipex(&pipex, envp);
	safe_exit(&pipex, 0);
	return (EXIT_SUCCESS);
}

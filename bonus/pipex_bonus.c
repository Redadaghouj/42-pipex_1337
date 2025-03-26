/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:19:13 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/26 03:23:16 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	pipex->heredoc = 0;
	pipex->infile = argv[0];
	pipex->outfile = argv[(argc - 1)];
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
	pipex->cmd = pipex->argv[i + pipex->heredoc];
	pipex->cmd = ft_strrchr(pipex->cmd, '/', &pipex->slash);
	pipex->args = ft_split(pipex->cmd, ' ');
	pipex->full_path = ft_split(pipex->argv[i + pipex->heredoc], ' ');
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	init_t_pipex(argv + 1, argc - 1, &pipex);
	if (argc == 6 && ft_strcmp(argv[1], "here_doc") == 0)
		run_here_doc(argv[2], argv[5], &pipex);
	else if (argc < 5)
		return (EXIT_FAILURE);
	check_infile_permission(&pipex);
	get_cmd_paths(envp, &pipex);
	run_pipex(&pipex, envp);
	safe_exit(&pipex, 0);
	return (EXIT_SUCCESS);
}

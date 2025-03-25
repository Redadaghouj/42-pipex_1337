/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:19:13 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/25 03:21:30 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_pipex(t_pipex *pipex, char *envp[])
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return ;
	if (ft_fork(pipex) == 0)
		first_child(pipex, pipefd, envp);
	if (ft_fork(pipex) == 0)
		second_child(pipex, pipefd, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
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

void	get_args(t_pipex *pipex)
{
	pipex->cmd1 = ft_strrchr(pipex->cmd1, '/', &pipex->slash1);
	pipex->cmd2 = ft_strrchr(pipex->cmd2, '/', &pipex->slash2);
	pipex->args1 = ft_split(pipex->cmd1, ' ');
	pipex->args2 = ft_split(pipex->cmd2, ' ');
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		return (EXIT_FAILURE);
	init_t_pipex(argv + 1, &pipex);
	if (check_file_permission(&pipex) < 0)
		return (EXIT_FAILURE);
	get_cmd_paths(envp, &pipex);
	get_args(&pipex);
	run_pipex(&pipex, envp);
	safe_exit(&pipex, 0);
	return (EXIT_SUCCESS);
}

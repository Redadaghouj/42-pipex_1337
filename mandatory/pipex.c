/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:19:13 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/22 21:47:34 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_pipex(t_pipex *pipex, char **cmd_paths)
{
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		safe_exit(pipex, cmd_paths);
	else if (ft_fork(pipex, cmd_paths) == 0)
		first_child(pipex, pipefd, cmd_paths);
	else if (ft_fork(pipex, cmd_paths) == 0)
		second_child(pipex, pipefd, cmd_paths);
	wait(NULL);
}

char	**get_cmd_paths(char *envp[])
{
	int		i;
	char	**cmd_paths;

	cmd_paths = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strstr(envp[i], "PATH") != NULL)
		{
			cmd_paths = ft_split(&envp[i][5], ':');
			break;
		}
		i++;
	}
	return (cmd_paths);
}

void	ll(void)
{
	system("leaks -q pipex");
}

int	main(int argc, char *argv[], char *envp[])
{
	atexit(ll);
	t_pipex	pipex;
	char	**cmd_paths;

	if (argc != 5)
		return (EXIT_FAILURE);
	init_t_pipex(argv + 1, &pipex);
	if (check_file_permission(&pipex) < 0)
		return(EXIT_FAILURE);
	cmd_paths = get_cmd_paths(envp);
	run_pipex(&pipex, cmd_paths);
	return (EXIT_SUCCESS);
}

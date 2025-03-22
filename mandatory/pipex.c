/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:19:13 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/22 03:48:55 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_pipex(t_pipex *pipex, char **cmd_paths)
{
	int		pipefd[2];
	int		pid;
	int		i;
	char	*path;

	if (pipe(pipefd) == -1)
		safe_exit(pipex);
	pid = fork();
	if (pid == -1)
		safe_exit(pipex);
	if (pid == 0)
	{
		close(pipefd[1]);
		dup3(pipex->infile_fd, STDIN_FILENO);
		dup3(pipex->outfile_fd, STDOUT_FILENO);
		i = 0;
		while (cmd_paths[i] != NULL)
		{
			path = ft_strjoin(cmd_paths[i], pipex->cmd1);
			execv(path, ft_split(pipex->cmd1, ' '));
			free(path);
			i++;
		}
		exit(EXIT_FAILURE);
	}
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

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	char	**cmd_paths;

	if (argc != 5)
		return (EXIT_FAILURE);
	init_t_pipex(argv + 1, &pipex);
	pipex.infile_fd = check_infile_permission(pipex.infile);
	pipex.outfile_fd = check_outfile_permission(pipex.outfile);
	if (pipex.infile_fd < 0 || pipex.outfile_fd < 0)
		return(EXIT_FAILURE);
	cmd_paths = get_cmd_paths(envp);
	run_pipex(&pipex, cmd_paths);
	return (EXIT_SUCCESS);
}

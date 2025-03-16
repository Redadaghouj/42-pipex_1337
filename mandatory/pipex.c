/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:19:13 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/16 02:51:05 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int		pipefd[2];
	int		pid;

	if (pipe(pipefd) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		char *arg[] = {"wc", "-l", NULL};
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		printf("Child process: Running 'wc -l'\n");
		execve("/usr/bin/wc", arg, NULL);
	}
	else
	{
		close(pipefd[0]);
		write(pipefd[1], "line\nline\nline\n", 16);
		printf("Parent process: Sent data to child\n");
		close(pipefd[1]);
	}
	return (EXIT_SUCCESS);
}

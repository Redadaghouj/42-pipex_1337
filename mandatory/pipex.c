/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:19:13 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/20 09:46:10 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_msg(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	int		pipefd[2];
	int		pid;

	if (pipe(pipefd) == -1)
		error_msg();
	pid = fork();
	if (pid == -1)
		error_msg();
	else if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		char *args[] = {"ls", NULL};
		if (execve("/bin/ls", args, NULL) == -1)
			error_msg();	
	}
	int pid2 = fork();
	if (pid2 == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		char *args[] = {"wc", "-l", NULL};
		if (execve("/usr/bin/wc", args, NULL) == -1)
			error_msg();		
	}
	close(pipefd[1]);
	close(pipefd[0]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (EXIT_SUCCESS);
}

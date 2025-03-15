/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:19:13 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/15 03:41:35 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int status;
	pid_t pid = fork();
	if (pid == -1)
		perror("Error");
	else if (pid == 0)
	{
		printf("Child process PID = %d is running\n", getpid());
		sleep(10);
		printf("Child exiting\n");
		exit(10);
	}
	else
	{
		waitpid(pid, &status, WNOHANG);
		if (!WIFEXITED(status))
			printf("The child still not exit\n");
		printf("Parent exiting\n");
	}
	return (EXIT_SUCCESS);
}

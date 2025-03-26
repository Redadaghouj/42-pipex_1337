/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 07:28:58 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/26 01:02:36 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_heredoc_permission(char *file, int *fd)
{
	*fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (*fd < 0)
	{
		perror("Error");
		exit(1);
	}
}

void	run_here_doc(char *limiter, char *file, t_pipex *pipex)
{
	int		pipefd[2];
	char	*line;

	check_heredoc_permission(file, &pipex->outfile_fd);
	if (pipe(pipefd) == -1)
		return ;
	pipex->infile_fd = pipefd[0];
	limiter = ft_strjoin_gnl(limiter, "\n");
	while (1)
	{
		ft_putstr("pipex here_doc> ");
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			free(limiter);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipefd[1]);
}

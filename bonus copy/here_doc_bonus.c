/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda <reda@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 07:28:58 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/25 21:12:24 by reda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	run_here_doc(char *limiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		return ;
	dup3(pipefd[1], STDOUT_FILENO);
	dup3(pipefd[0], STDIN_FILENO);
	limiter = ft_strjoin_gnl(limiter, "\n");
	while (1)
	{
		ft_putstr("pipex here_doc> ");
		line = get_next_line(STDIN_FILENO);
		if (ft_strcmp(line, limiter) == 0 || !line)
		{
			free(line);
			free(limiter);
			break ;
		}
		free(line);
	}
}

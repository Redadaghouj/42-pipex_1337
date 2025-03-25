/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 07:28:58 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/25 08:45:26 by mdaghouj         ###   ########.fr       */
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
	// dup3(pipefd[0], STDIN_FILENO);
	ft_putstr("pipex here_doc> ");
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		ft_putstr("pipex here_doc> ");
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:19:13 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/21 00:36:41 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	pipex(int a)
// {
	
// }

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		outfile_fd;
	int		infile_fd;

	if (argc != 5)
		return (EXIT_FAILURE);
	init_t_pipex(argv + 1, &pipex);
	infile_fd = check_infile_permission(pipex.infile);
	outfile_fd = check_outfile_permission(pipex.outfile);
	if (infile_fd < 0 || outfile_fd < 0)
		return(EXIT_FAILURE);
	// run_pipex(1);
	return (EXIT_SUCCESS);
}

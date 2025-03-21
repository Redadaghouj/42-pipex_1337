/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:17:52 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/21 00:24:59 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h> // -REMOVE-
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <strings.h>
# include <errno.h>

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

typedef struct s_pipex
{
	char	*infile;
	char	*cmd1;
	char	*cmd2;
	char	*outfile;
}			t_pipex;

/* PIPEX_UTILS */
void	init_t_pipex(char **argv, t_pipex *pipex);
int		check_infile_permission(char *file);
int		check_outfile_permission(char *file);

/* ERROR_HANDLERS */
void	print_error(char *msg, char *file);

/* UTILS FUNCTIONS */
void	ft_putstr(char *s);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);

#endif
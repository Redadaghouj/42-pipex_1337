/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:17:52 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/24 07:00:33 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <strings.h>
# include <errno.h>
# include <sys/wait.h>
# include "gnl/get_next_line_bonus.h"

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

typedef struct s_pipex
{
	char	*infile;
	char	*cmd;
	char	*outfile;
	int		infile_fd;
	int		outfile_fd;
	char	**cmd_paths;
	char	**args;
	char	*full_arg;
	char	*path;
	char	**argv;
	int		slash;
	int		count;
}			t_pipex;

void	get_args(t_pipex *pipex, int i);

/* PIPEX_UTILS */
void	init_t_pipex(char **argv, int argc, t_pipex *pipex);
int		check_file_permission(t_pipex *pipex);
int		dup3(int old_fd, int new_fd);
int		ft_fork(t_pipex *pipex);
void	*free_buffer(char **buffer);

/* ERROR_HANDLERS */
void	print_error(char *msg, char *file);
void	safe_exit(t_pipex *pipex, int err);

/* PROCESS */
void	child_process(t_pipex *pipex, char *envp[]);

/* UTILS */
void	ft_putstr(char *s);
char	**ft_split(char const *s, char c);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strrchr(const char *s, int c, int *slash);

#endif
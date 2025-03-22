/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:17:52 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/22 21:47:32 by mdaghouj         ###   ########.fr       */
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
# include <limits.h>

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

typedef struct s_pipex
{
	char	*infile;
	char	*cmd1;
	char	*cmd2;
	char	*outfile;
	int		infile_fd;
	int		outfile_fd;
}			t_pipex;

/* PIPEX_UTILS */
void	init_t_pipex(char **argv, t_pipex *pipex);
int		check_file_permission(t_pipex *pipex);
int		dup3(int old_fd, int new_fd);
int		ft_fork(t_pipex *pipex, char **cmd_path);
void	*free_buffer(char **buffer);

/* ERROR_HANDLERS */
void	print_error(char *msg, char *file);
void	safe_exit(t_pipex *pipex, char **cmd_path);

/* CHILDREN */
void	first_child(t_pipex *pipex, int pipefd[], char **cmd_paths);
void	second_child(t_pipex *pipex, int pipefd[], char **cmd_paths);

/* UTILS */
void	ft_putstr(char *s);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strjoin(char *s1, char *s2);

#endif
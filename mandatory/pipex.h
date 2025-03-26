/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:17:52 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/26 03:51:12 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

typedef struct s_pipex
{
	char	*cmd;
	int		infile_fd;
	int		outfile_fd;
	char	**cmd_paths;
	char	**args;
	char	**full_path;
	char	*path;
	char	**argv;
	int		slash;
	int		count;
	char	*infile;
	char	*outfile;
}			t_pipex;

void	get_args(t_pipex *pipex, int i);

/* PIPEX_UTILS */
void	init_t_pipex(char **argv, int argc, t_pipex *pipex);
void	check_infile_permission(t_pipex *pipex);
void	check_outfile_permission(t_pipex *pipex, int pipefd[]);
int		dup3(int old_fd, int new_fd);
int		ft_fork(t_pipex *pipex);
void	*free_buffer(char **buffer);
void	parent_cleanup(int *prev_fd, int count, int pipefd[], int i);

/* ERROR_HANDLERS */
void	safe_exit(t_pipex *pipex, int err);
void	fail_cmd_error(t_pipex *pipex, char *cmd);

/* CHILD PROCESS */
void	execute_child(t_pipex *pipex, char *envp[]);
void	setup_child_process(t_pipex *pipex, int i, int pipefd[], int prev_fd);

/* UTILS */
void	ft_putstr(char *s);
char	**ft_split(char const *s, char c);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strrchr(const char *s, int c, int *slash);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);

#endif
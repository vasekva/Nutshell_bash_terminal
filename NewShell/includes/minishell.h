/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 07:20:24 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 07:20:26 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
 *:::::::::::::::::::::::::::::::::::::::::::	INCLUDES
 */
# include <stdio.h>
# include <string.h>
//# include <unistd.h>
//# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>

# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>

# include "exceptions.h"
# include "my_readline.h"
# include "libft.h"

/*
 *:::::::::::::::::::::::::::::::::::::::::::	DEFINES
 */
# define	BUFFER_SIZE 32
# define	TRUE 1
# define	FALSE 0

int	error_code;

/*
 *:::::::::::::::::::::::::::::::::::::::::::	STRUCTURES
 */
typedef struct s_data		t_data;
typedef struct s_cmd		t_cmd;
typedef struct s_redir_list	t_redir_list;
typedef struct s_env_list	t_env_list;

struct s_cmd
{
	int 	fd[2];
	int 	fd_output;
	int 	fd_input;

	char	**command;
	int		num_args;

	int 	        is_redirect;
    t_redir_list    *r_list;

	t_cmd	*prev;
	t_cmd	*next;
};

struct s_env_list
{
	char		*key;
	char		*value;
	char		*str;
	t_env_list	*next;
	t_env_list	*past;
};

struct s_redir_list
{
	char		    *filename;
	t_redir_list	*next;
};

struct s_data
{
	char		*title;

	char		*curr_dir;
	char		*past_dir;
	t_cmd		*list_cmds;
	t_env_list	*env_node; //список переменных окружения
};

int		deff_curr_cmd(t_data *shell, t_cmd *node);
void	exception(char *command, char *variable, char *message);

int		ft_cd(t_data *shell);
void	ft_cd_updir(t_data *shell);
void	ft_cd_cut_path(t_data *shell, t_cmd *s_cmd);

void	change_dirs(t_data *shell, char *new_path, char *dst_path_key);

int		ft_echo(t_data *shell);
void	ft_env(t_data *shell);
void	ft_execve(t_data *shell);
void	ft_exit(t_data *shell);
void	ft_export(t_data *shell);
void	ft_pwd(void);
void	ft_unset(t_data *shell);

/*
** UTILS_FOR_ARRAY_1.C
*/
void	arr_free(char **array);

/*
 * UTILS_FOR_LIST.C
 */
void		push_back(t_env_list **env_node, char *key, char *value, char *str);
void		list_sort(t_env_list *list);
int			list_length(const t_env_list *list);
char		*get_value_by_key(t_env_list *list, char *key);
t_env_list	*get_last(t_env_list *env_node);
t_env_list	*get_node_by_content(t_env_list *list, char *content, int flag);
void		free_node_content(t_env_list *node);


/*
 * INIT.C
 */
void	init_logs(t_data *shell, char *envp[]);

/*
 * SIGNALS.C
 */
void	signal_handler(int signal);

/*
 * REDIRECTS.C
 */
void	open_filenames_fd(t_cmd *node);

/*
 * PIPES.C
 */
void	ft_start_shell(t_data *shell);

/*
 * :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::  PARSER  :::::
 */
int		syntax_check(const char *line);
void	preparser(t_data *shell, char *line);
char	**split_arguments(const char *command, char c);
/*
 *................... work with redirects
 */
void	refactor_redirects(char **line, t_redir_list **r_list);
char    *cut_filenames(char **str, int *i, int len);

/*
 * ............... work with $ and quotes
 */
char	*lexer(t_data *shell, char *line, int num_arg);
/*
 * ........................  PARSER UTILS
 */
void	switcher(char symbol, int *d_q_flag, int *s_q_flag);
char	*ft_replace_dollar(const char *line, int i_left, int i_right, char *new);
char	*ft_divide_by_quotes(const char *line, int i_left, int i_right);

#endif

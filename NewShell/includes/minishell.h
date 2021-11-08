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
 * :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::  INCLUDES  :::::
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
 * ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::  DEFINES  :::::
 */
# define BUFFER_SIZE	32
# define PARENT	1
# define CHILD	0
# define REDIRECT_INPUT			1
# define REDIRECT_INPUT_HEREDOC	2
# define REDIRECT_OUTPUT		3
# define REDIRECT_OUTPUT_DOUBLE	4

int							g_err_code;

/*
 * :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::  STRUCTURES  :::::
 */
typedef struct s_data		t_data;
typedef struct s_cmd		t_cmd;
typedef struct s_redir_list	t_redir_list;
typedef struct s_env_list	t_env_list;

struct s_cmd
{
	int				fd[2];
	int				fd_output;
	int				fd_input;

	char			**command;
	int				num_args;

	int				is_redirect;
	t_redir_list	*r_list;

	t_cmd			*prev;
	t_cmd			*next;
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
	char			*filename;
	int				type;
	t_redir_list	*next;
};

struct s_data
{
	char		*title;
	char		*home;

	char		*curr_dir;
	char		*past_dir;
	t_cmd		*list_cmds;
	t_env_list	*env_node;
};

/*
 * :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::  FUNCTIONS  :::::
 */
int			deff_curr_cmd(t_data *shell, t_cmd *node);
void		exception(char *command, char *variable, char *message);

int			ft_cd(t_data *shell, t_cmd *node);
int			ft_cd_replace_paths(t_data *shell);
void		ft_cd_updir(t_data *shell);
void		relative_path(t_data *shell, t_cmd *s_cmd);

void		change_dirs(t_data *shell, char *new_path, char *dst_path_key);

int			ft_echo(t_cmd *node);
void		ft_env(t_data *shell);
void		ft_execve(t_data *shell, t_cmd *node);
int			ft_exit(t_data *shell, t_cmd *node);
void		ft_export(t_data *shell);
void		ft_pwd(void);
void		ft_unset(t_data *shell, t_cmd *cmd_node);

/*
 * CMDS_UTILS.C
 */
int	has_file(char *path);

/*
 *....... UTILS_FOR_ARRAY_1.C
*/
void		arr_free(char **array);

/*
 *.......... UTILS_FOR_LIST.C
 */
void		push_back(t_env_list **env_node, char *key, char *value, char *str);
void		list_sort(t_env_list *list);
int			list_length(const t_env_list *list);
char		*get_value_by_key(t_env_list *list, char *key);
t_env_list	*get_last(t_env_list *env_node);
t_env_list	*get_node_by_content(t_env_list *list, char *content, int flag);
void		free_node_content(t_env_list *node);

/*
 *.................... INIT.C
 */
void		init_logs(t_data *shell, char *envp[]);

/*
 *................. SIGNALS.C
 */
void		set_signal_handler(int process_pid);

/*
 *............... REDIRECTS.C
 */
void		open_filenames_fd(t_cmd *node);

/*
 *................... PIPES.C
 */
void		ft_start_shell(t_data *shell);

/*
 * :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::  PARSER  :::::
 */
int			syntax_check(const char *line);
void		preparser(t_data *shell, char *line);
char		**split_arguments(const char *command, char c);
/*
 *................... work with redirects
 */
void		refactor_redirects(char **line, t_redir_list **r_list);
char		*cut_filenames(char **str, int *i);

/*
 * ............... work with $ and quotes
 */
char		*lexer(t_data *shell, char *line, int num_arg);
/*
 * ........................  PARSER UTILS
 */
void		switcher(char symbol, int *d_q_flag, int *s_q_flag);
char		*ft_replace_dollar(const char *line, int i_left, int i_right, \
																char *new);
char		*ft_divide_by_quotes(const char *line, int i_left, int i_right);
void		replace_line_by_key(t_env_list *env_node, char **line, \
													int *index, int i_start);
void		replace_line_by_nextchar(char **line, int index, int i_start, \
																char nxt_c);

#endif

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
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>

# include <sys/stat.h>
//# include <sys/types.h>

# include "libft.h"
# include "exceptions.h"
# include "my_readline.h"

/*
 *:::::::::::::::::::::::::::::::::::::::::::	DEFINES
 */
# define	BUFFER_SIZE 32
# define	TRUE 1
# define	FALSE 0

/*
 *:::::::::::::::::::::::::::::::::::::::::::	STRUCTURES
 */
typedef struct s_data	t_data;
typedef struct s_cmd	t_cmd;

struct s_cmd
{
	char	**command;
	int		num_args;
	t_cmd	*next;
};

struct s_data
{
	char	*title;
	char	**envp_copy;

	t_cmd	*list_cmds;
};

int		get_next_line(int fd, char **line);


int		deff_curr_cmd(t_data *shell);
void	exception(char *str);

int		ft_cd(t_data *shell);
int		ft_echo(t_data *shell);
void	ft_env(t_data *shell);
void	ft_execve(t_data *shell);
void	ft_exit(t_data *shell);
void	ft_export(t_data *shell);
void	ft_pwd(void);
void	ft_unset(t_data *shell);

/*
** ARRAY_RESIZE.C
*/
char	**array_resize(char **src, int flag);

/*
** UTILS_FOR_ARRAY_1.C
*/
int		arr_get_str_ind(t_data *shell, char *str);
void	arr_add_var(t_data *shell, char *key, char *value);
void	arr_swap_strings(char **array, int first, int second);
void	arr_free(char **array);
char	**arr_sort(char **array);

/*
** UTILS_FOR_ARRAY_2.C
*/
char	**arr_copy(char **array);

/*
** UTILS_FOR_ARRAY_3.C
*/
int	env_find_str_ind_by_key(char **array, char *key);
int	get_symbol_ind(char *str, char symbol);
char *env_get_value_by_key(char **array, char *key);

/*
** FT_ENV_UTILS.C
*/
char	*get_value(t_data *shell, char *key);
char	*replace_value(t_data *shell, char *key, char *new_value);
void	copy_value(t_data *shell, char *src, char *dst);
void	swap_values(t_data *shell, char *key_fst, char *key_scnd);

/*
 * INIT.C
 */
void	init_logs(t_data *shell, char *envp[]);

/*
 * PARSER
 */
int		syntax_check(const char *line);
void	preparser(t_data *shell, char *line);
char	**split_arguments(const char *command, char c);
char	*lexer(t_data *shell, char *line);
char	*ft_replace_dollar(const char *line, int i_left, int i_right, char *new);
char	*ft_divide_by_quotes(const char *line, int i_left, int i_right);

#endif

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
# define BUFFER_SIZE 32
# define	TRUE 1
# define	FALSE 0

/*
 *:::::::::::::::::::::::::::::::::::::::::::	STRUCTURES
 */
typedef struct s_loginfo	t_loginfo;
typedef struct s_cmd		t_cmd;

struct s_cmd
{
	char	**command;
	int		num_args;
	t_cmd	*next;
};

struct s_loginfo
{
	char	*title;
	char	**envp_copy;

	t_cmd	*commands;
};

//void	arr_free(char **array);

int		get_next_line(int fd, char **line);


int		deff_curr_cmd(t_loginfo *shell);
void	exception(char *str);

int		ft_cd(t_loginfo *shell);
int		ft_echo(t_loginfo *shell);
void	ft_env(t_loginfo *shell);
void	ft_execve(t_loginfo *shell);
void	ft_exit(t_loginfo *shell);
void	ft_export(t_loginfo *shell);
void	ft_pwd(void);
void	ft_unset(t_loginfo *shell);

/*
** ARRAY_RESIZE.C
*/
char	**array_resize(char **src, int flag);

/*
** UTILS_FOR_ARRAY_1.C
*/
int		arr_get_str_ind(t_loginfo *shell, char *str);
void	arr_add_var(t_loginfo *shell, char *key, char *value);
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
char	*get_value(t_loginfo *shell, char *key);
char	*replace_value(t_loginfo *shell, char *key, char *new_value);
void	copy_value(t_loginfo *shell, char *src, char *dst);
void	swap_values(t_loginfo *shell, char *key_fst, char *key_scnd);

/*
 * INIT.C
 */
void	init_logs(t_loginfo *shell, char *envp[]);

/*
 * PARSER
 */
char	*lexer(t_loginfo *shell, char *line);
char	*ft_dollar_replacer(const char *line, int i_left, int i_right, char *part_to_replace);

#endif

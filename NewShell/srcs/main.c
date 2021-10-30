/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 07:17:51 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 07:17:52 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	ft_free_data(t_data *shell, char *line)
{
	t_cmd			*ptr;
	t_cmd			*tmp;
	t_redir_list	*tmp_redir;

	free(line);
	line = NULL;
	ptr = shell->list_cmds;
	while (ptr != NULL)
	{
		arr_free(ptr->command);
		ptr->num_args = 0;
		ptr->fd_input = 0;
		ptr->fd_output = 1;
		ptr->is_redirect = 0;
		while (ptr->r_list)
		{
			free(ptr->r_list->filename);
			tmp_redir = ptr->r_list;
			ptr->r_list = ptr->r_list->next;
			tmp_redir->next = NULL;
			free(tmp_redir);
			tmp_redir = NULL;
		}
		tmp = ptr;
		ptr = ptr->next;
		tmp->next = NULL;
		tmp->prev = NULL;
		free(tmp);
		tmp = NULL;
	}
	shell->list_cmds = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	shell;
	char	*line;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
//	rl_catch_signals = 0;
	init_logs(&shell, envp);
	while (1)
	{
		line = readline(shell.title);
		if (!line)
			line = ft_strdup("exit");
		if (line[0])
			add_history(line);
		if (!syntax_check(line))
		{
			preparser(&shell, line);
			ft_start_shell(&shell);
		}
        ft_free_data(&shell, line);
	}
	return (0);
}

//TODO: env_get_value_by_key() теперь возвращает указатель на строку, (node->value)
// взятую из узла списка, в котором был найден подходящий ключ (node->key)
// не уверен, безопасно ли это в плане утечек при удалении, либо замены
// узла, из которого взят указатель

//TODO: -Wall -Wextra -Werror -g ??????

/*
 * unset TERM_SESSION_ID SSH_AUTH_SOCK LC_TERMINAL_VERSION Apple_PubSub_Socket_Render _ HOMEBREW_TEMP HOMEBREW_CACHE LSCOLORS COLORFGBG ITERM_PROFILE XPC_FLAGS LANG PWD SECURITYSESSIONID TERM_PROGRAM_VERSION TERM_PROGRAM LC_TERMINAL COLORTERM COMMAND_MODE __CF_USER_TEXT_ENCODING ITERM_SESSION_ID LESS PAGER ZSH USER TERM PATH HOME TMPDIR XPC_SERVICE_NAME LOGNAME SHLVL OLDPWD
 */

/*
 * unset $HOME $SHLVL | unset $LESS $USER $PWD | unset $SHELL $PAGER
 */
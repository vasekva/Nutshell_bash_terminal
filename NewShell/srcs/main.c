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

/*
 * Запускает функцию в которой определяется команда,
 * которую необходимо выполнить
 */
static int	ft_start_shell(t_data *shell)
{
	if (shell->list_cmds)
	{
		if (!deff_curr_cmd(shell))
			return (0);
		else
			return (1);
	}
	return (0);
}

void	ft_free_data(t_data *shell, char *line)
{
	t_cmd	*ptr;
	t_cmd	*tmp;

	free(line);
	line = NULL;
	ptr = shell->list_cmds;
	while (ptr != NULL)
	{
		arr_free(ptr->command);
		ptr->num_args = 0;
		tmp = ptr;
		ptr = ptr->next;
		tmp->next = NULL;
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
			if (shell.list_cmds && shell.list_cmds->command[0])
				ft_start_shell(&shell);
		}
        ft_free_data(&shell, line);
	}
	return (0);
}
//TODO: 'll' производит вывод)

//TODO: неккоректный вывод 'syntax error'. Надо постараться связать его с exception();
//TODO: сделать OLDPWD при смене директории (изначально этой переменной нет)
//TODO: (возможно) сделать отдельную функцию для смены директории, ибо часто используется
// смена текущей и в последствии предыдущей директорий

//TODO: env_get_value_by_key() теперь возвращает указатель на строку, (node->value)
// взятую из узла списка, в котором был найден подходящий ключ (node->key)
// не уверен, безопасно ли это в плане утечек при удалении, либо замены
// узла, из которого взят указатель

/*
 * unset TERM_SESSION_ID SSH_AUTH_SOCK LC_TERMINAL_VERSION Apple_PubSub_Socket_Render _ HOMEBREW_TEMP HOMEBREW_CACHE LSCOLORS COLORFGBG ITERM_PROFILE XPC_FLAGS LANG PWD SECURITYSESSIONID TERM_PROGRAM_VERSION TERM_PROGRAM LC_TERMINAL COLORTERM COMMAND_MODE __CF_USER_TEXT_ENCODING ITERM_SESSION_ID LESS PAGER ZSH USER TERM PATH HOME TMPDIR XPC_SERVICE_NAME LOGNAME SHLVL OLDPWD
 */
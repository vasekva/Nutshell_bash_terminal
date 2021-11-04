/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 06:09:47 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/04 06:09:49 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Функция создает список на основе содержимого
 * двумерного массива переменных окружения.
 *
 * Функция в цикле 'потрошит' полученную
 * переменную окружения на:
 * 'key' - значение строки до знака '=',
 * 'value' - значение строки после знака '=',
 * 'str' - изначальная строка переменной окружения
 * и с помощью push_back(...) создает в конце списка
 * новый узел, передавая в функцию создания узла
 * три полученных значения
 *
 * @param shell: Структура в которой лежит
 * указатель на заполняемый список.
 *
 * @param envp: Двумерный массив переменных окружения,
 * который будет копироваться в список.
 */
void	copy_env_to_list(t_data *shell, char **envp)
{
	char	*key;
	char	*value;
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (envp[++i])
	{
		while (envp[i][++j])
		{
			if (envp[i][j] == '=')
			{
				key = ft_substr(envp[i], 0, j);
				value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j);
				str = ft_strdup(envp[i]);
				push_back(&shell->env_node, key, value, str);
			}
		}
		j = -1;
	}
}

void	init_logs(t_data *shell, char **envp)
{
	shell->title = ft_strjoin(getenv("LOGNAME"), "/minishell/$> ", -1);
	shell->curr_dir = getcwd(NULL, 0);
	shell->past_dir = ft_strdup(shell->curr_dir);
	if (!shell->title)
		exception(NULL, NULL, MALLOC_ERROR);
	shell->env_node = NULL;
	copy_env_to_list(shell, envp);
	shell->list_cmds = NULL;
}

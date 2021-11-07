/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:18:46 by jberegon          #+#    #+#             */
/*   Updated: 2021/08/04 15:18:53 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_write_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (0);
}

/*
 * Функция проходится по переданным аргументам начиная с полученного индекса(ind)
 * и выводит их в консоль с помощью ft_write_str, разделяя строки пробелом
 * и если флаг отвечающий за '-n' нулевой - переводит строчку
 */
static void	write_lines(t_cmd *s_cmd, int ind, int flag)
{
	char	*str;

	while (ind < s_cmd->num_args)
	{
		str = s_cmd->command[ind];
		ft_write_str(str);
		if (ind + 1 != s_cmd->num_args)
			write(1, " ", 1);
		ind++;
	}
	if (!flag)
		write(1, "\n", 1);
}

/*
 * Вспомогательная функция для has_delete_nline
 * Функция проверяет правильность расположения символов '-' и 'n'
 * и возвращает индекс строки(слова) в случае найденной ошибки
 * иначе возвращает 0
 */
static int	check_line(char *str, int ret_ind)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[0] != '-' || str[1] != 'n')
			return (ret_ind);
		if (j >= 1)
		{
			if (str[j] != 'n' && str[j] != '-')
				return (ret_ind);
			if (str[j - 1] == 'n' && str[j] == '-')
				return (ret_ind);
		}
		j++;
	}
	return (0);
}

/*
 * Функция проходится по строкам параметров и передает каждую строчку
 * в check_line для проверки валидности расположения символов в ней,
 * в случае положительного возврата от check_line возвращает индекс
 * от check_line, иначе возвращает -1
 */
static int	has_delete_nline(t_cmd *s_cmd)
{
	int		ret;
	char	*tmp;
	int		line_ind;

	line_ind = 1;
	while (s_cmd->command[line_ind])
	{
		tmp = s_cmd->command[line_ind];
		ret = check_line(tmp, line_ind);
		if (ret)
			return (ret);
		line_ind++;
	}
	return (-1);
}

int	ft_echo(t_cmd *node)
{
	int		ind;
	int		flag;
	char	*first_arg;
	t_cmd	*s_cmd;

	s_cmd = node;
	// Если команда 'echo' без параметров
	if (!s_cmd->command[1])
		return (write(1, "\n", 1));
	ind = -1;
	flag = 0;
	first_arg = s_cmd->command[1];
	// Если введена команда echo -n
	if ((first_arg[0] == '-' && first_arg[1] == 'n')
		&& s_cmd->num_args == 2)
		return (1);
	// Если задана команда 'echo -n ...'
	if (first_arg[0] == '-' && first_arg[1] == 'n')
	{
		ind = has_delete_nline(s_cmd);
		if (ind && ind != 1)
			flag = 1;
	}
	if (ind < 0)
		ind = 1;
	write_lines(s_cmd, ind, flag);
	return (1);
}

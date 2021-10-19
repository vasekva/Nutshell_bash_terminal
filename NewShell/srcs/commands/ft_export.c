/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 07:07:54 by jberegon          #+#    #+#             */
/*   Updated: 2021/09/02 07:07:56 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_without_params(t_data *shell)
{
	t_env_list	*env_node;
	char		*tmp_str;

	if (!shell->env_node)
		return ;
	env_node = shell->env_node;
	list_sort(env_node);
	while (env_node)
	{
		tmp_str = ft_strjoin("declare -x ", env_node->str, -1);
		printf("%s\n", tmp_str);
		free(tmp_str);
		env_node = env_node->next;
	}
}

void	ft_export(t_data *shell)
{
	if (shell->list_cmds->command[1] == NULL)
	{
		export_without_params(shell);
		return ;
	}
}

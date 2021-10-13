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
	char	**arr_export;
	char	*tmp_str;
	int		i;

	i = 0;
	arr_export = NULL;
	arr_export = arr_sort(shell->envp_copy);
	while (arr_export[i])
	{
		tmp_str = ft_strjoin("declare -x ", arr_export[i], 3);
		printf("%s\n", tmp_str);
		free(tmp_str);
		i++;
	}
	arr_free(arr_export);
}

void	ft_export(t_data *shell)
{
	int	i;

	i = 0;
	if (shell->list_cmds->command[1] == NULL)
	{
		export_without_params(shell);
		return ;
	}
}

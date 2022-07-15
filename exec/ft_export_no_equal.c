/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_equal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:30:09 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/15 17:21:56 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	ft_export_no_equal(struct s_environ *envp, t_cmd *cmd, int i)
{
	int					x;
	struct s_environ	*tmp;

	tmp = envp;
	x = 0;
	if (check_name_is_valid(&cmd->cmd[i], i, cmd) == 1)
		return (UNSUCCESSFUL);
	while (tmp)
	{
		if (ft_strncmp(tmp->name, cmd->cmd[i], ft_strlen(cmd->cmd[i]) + 1) == 0)
		{
			printf(" name %s    args to export %s\n", tmp->name, cmd->cmd[i]);
			return (SUCCESSFUL);
		}
		tmp = tmp->next;
	}
	ftaddback(&envp, cmd->cmd[i]);
	ftsplitenv(envp, x);
	return (SUCCESSFUL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_equal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:30:09 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/13 10:34:35 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	copy(struct s_envp *envp, t_cmd *cmd, int i, char **new)
{
	int	t;

	t = 0;
	while (t < envp->envpitems)
	{
		new[t] = envp->environment[t];
		t++;
	}
	new[t] = cmd->cmd[i];
	new[t + 1] = NULL;
	envp->envpitems++;
	ft_copy_1st_env(envp, new);
	return (SUCCESSFUL);
}

int	ft_export_no_equal(struct s_envp *envp, t_cmd *cmd, int i, char **new)
{
	int	x;

	x = 0;
	if (check_name_is_valid(&cmd->cmd[i], i, cmd) == 1)
		return (UNSUCCESSFUL);
	while (x < envp->envpitems)
	{
		if (ft_strncmp(envp->name[x], cmd->cmd[i], ft_strlen(cmd->cmd[i])
				+ 1) == 0)
		{
			return (SUCCESSFUL);
		}
		x++;
	}
	copy(envp, cmd, i, new);
	return (SUCCESSFUL);
}

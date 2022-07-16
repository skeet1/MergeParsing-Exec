/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:26:24 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/16 08:29:05 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	modify_name(struct s_environ *envp, t_cmd *cmd, char **split, int i)
{
	int	x;
	int	t;

	x = 0;
	t = 0;
	x = 0;
	while (envp)
	{
		if (ft_strncmp(envp->name, split[0], ft_strlen(split[0]) + 1) == 0)
		{
			while (cmd->cmd[i][t])
			{
				if (cmd->cmd[i][t] == '=')
				{
					envp->env = cmd->cmd[i];
					return (0);
				}
				t++;
			}
			t = 0;
		}
		envp = envp->next;
	}
	return (1);
}

int	valid_identifier(struct s_environ *envp, t_cmd *cmd, int i)
{
	if (cmd->cmd[i][0] == '=')
	{
		printf("Minishell: export: `%s': not a valid identifier\n",
			cmd->cmd[i]);
		return (UNSUCCESSFUL);
	}
	return (SUCCESSFUL);
}

int	ft_export(struct s_environ *envp, t_cmd *cmd, int i)
{
	char	**split;
	int		x;

	if (valid_identifier(envp, cmd, i) == UNSUCCESSFUL)
		return (UNSUCCESSFUL);
	x = 0;
	while (cmd->cmd[i][x])
	{
		if (cmd->cmd[i][x] == '=')
		{
			split = ft_split(cmd->cmd[i], '=');
			if (check_name_is_valid(split, i, cmd) == 1)
				return (1);
			if (modify_name(envp, cmd, split, i) == 0)
				return (0);
			ftaddback(&envp, cmd->cmd[i]);
			ftsplitenv(envp, x);
			envp->envpitems++;
			return (SUCCESSFUL);
		}
		x++;
	}
	ft_export_no_equal(envp, cmd, i);
	return (SUCCESSFUL);
}

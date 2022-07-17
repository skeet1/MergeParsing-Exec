/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtcheck.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:40:43 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/16 21:43:32 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "../parsing/parse.h"

int	builtcheck(t_lis *envp, t_cmd *cmds)
{
	if (ft_strncmp(cmds->cmd[0], "echo", 5) == 0)
	{
		g_exit_status = ft_echo(cmds, cmds->fd_out);
		return (1);
	}
	else if (ft_strncmp(cmds->cmd[0], "cd", 3) == 0)
	{
		g_exit_status = ftcd(cmds, envp);
		return (1);
	}
	return (0);
}

int	builtcheck_next(t_cmd *cmd, t_lis *envp)
{
	int	i;

	i = 1;
	if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
	{
		i = 1;
		if (cmd->cmd[i] == NULL)
			return (0);
		while (cmd->cmd[i])
		{
			if (ft_equal_sign(cmd, i) == UNSUCCESSFUL)
			{
				g_exit_status = 1;
			}
			else
			{
				g_exit_status = ft_unset(envp, cmd, i);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

int	builtcheck_1(t_cmd *cmd, t_lis *envp)
{
	int	i;

	i = 1;
	if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
	{
		if (cmd->cmd[1] == NULL)
		{
			if (ft_export_1(envp) == 0)
				g_exit_status = 0;
			return (0);
		}
		while (cmd->cmd[i] != NULL)
		{
			g_exit_status = ft_export(envp, cmd, i);
			i++;
		}
		return (1);
	}
	if (builtcheck_next(cmd, envp) == 1)
	{
		return (1);
	}
	return (0);
}

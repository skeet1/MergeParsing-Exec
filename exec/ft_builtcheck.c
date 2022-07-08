/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtcheck.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:40:43 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/08 12:41:41 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "../parsing/parse.h"

int	builtcheck(t_cmdl *cmd, struct s_envp *envp)
{
	if (ft_strncmp(cmd[0].cmd, "echo", 5) == 0)
	{
		g_exit_status = ft_echo(cmd, cmd->fd_out);
		return (1);
	}
	else if (ft_strncmp(cmd[0].cmd, "cd", 3) == 0)
	{
		g_exit_status = ftcd(cmd, envp);
		return (1);
	}
	return (0);
}

int	builtcheck_next(t_cmdl *cmd, struct s_envp *envp)
{
	int	i;

	i = 0;
	if (ft_strncmp(cmd[0].cmd, "unset", 6) == 0)
	{
		i = 0;
		if (cmd[cmd->cmd_iteration].args[i] == NULL)
		{
			return (0);
		}
		while (cmd[cmd->cmd_iteration].args[i])
		{
			if (ft_equal_sign(envp, cmd, i) == 0)
			{
				g_exit_status = 1;
				return (1);
			}
			g_exit_status = ft_unset(envp, cmd, i);
			i++;
		}
		return (1);
	}
	return (0);
}

int	builtcheck_1(t_cmdl *cmd, struct s_envp *envp)
{
	int	i;

	i = 0;
	if (ft_strncmp(cmd[0].cmd, "export", 7) == 0)
	{
		if (cmd->args[0] == NULL)
		{
			if (ft_export_1(envp, cmd) == 0)
				return (0);
		}
		while (cmd[cmd->cmd_iteration].args[i] != NULL)
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

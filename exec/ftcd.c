/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:37:52 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/09 11:37:58 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	check_home_inenv(char *findhome, char *error)
{
	int	len;

	len = 0;
	if (findhome == NULL)
	{
		g_exit_status = 1;
		error = "Minishell: cd: HOME not set\n";
		len = ft_strlen(error);
		write(2, error, len);
		return (1);
	}
	return (0);
}

int	cd_last_check(t_cmd *cmd, char *error)
{
	int	len;

	len = 0;
	if (chdir(cmd->cmd[1]) == -1)
	{
		g_exit_status = 1;
		error = "Minishell: cd: No such file or directory\n";
		len = ft_strlen(error);
		write(2, error, len);
		return (1);
	}
	return (0);
}

int	ftcd_c(t_cmd *cmd)
{
	if (cmd->cmd[1] == NULL)
	{
		if (check_home_inenv(cmd->findhome, cmd->error) == 1)
			return (1);
	}
	if (cmd->cmd[1] == NULL)
	{
		chdir(cmd->findhome);
		return (0);
	}
	if (cmd->cmd[2] == NULL)
	{
		if (cd_last_check(cmd, cmd->error) == 1)
			return (1);
	}
	return (0);
}

int	ftcd(t_cmd *cmd, struct s_envp *envp)
{
	int	x;

	x = 0;
	cmd->findhome = NULL;
	while (x < envp->envpitems)
	{
		if (ft_strncmp(envp->name[x], "HOME", 5) == 0)
		{
			cmd->findhome = envp->value[x];
			break ;
		}
		x++;
	}
	if (ftcd_c(cmd) == 1)
		return (1);
	return (0);
}

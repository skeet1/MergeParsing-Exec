/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:37:52 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/17 08:27:40 by atabiti          ###   ########.fr       */
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
		return (UNSUCCESSFUL);
	}
	return (0);
}

int	cd_last_check(t_cmd *cmd)
{
	int	len;

	len = 0;
	if (chdir(cmd->cmd[1]) == -1)
	{
		ft_putstr_fd("Minishell: cd : ", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (UNSUCCESSFUL);
	}
	return (SUCCESSFUL);
}

int	ftcd_c(t_cmd *cmd)
{
	if (cmd->cmd[1] == NULL)
	{
		if (check_home_inenv(cmd->findhome, cmd->error) == UNSUCCESSFUL)
			return (UNSUCCESSFUL);
	}
	if (cmd->cmd[1] == NULL)
	{
		chdir(cmd->findhome);
		return (SUCCESSFUL);
	}
	else if (cmd->cmd[1] != NULL)
	{
		if (cd_last_check(cmd) == 1)
			return (1);
	}
	return (SUCCESSFUL);
}

int	ftcd(t_cmd *cmd, t_lis *envp)
{
	int		x;
	t_env	*envval;

	x = 0;
	envp = envp->next;
	cmd->findhome = NULL;
	while (envp)
	{
		envval = envp->content;
		if (ft_strncmp(envval->name, "HOME", 5) == 0)
		{
			cmd->findhome = envval->value;
			break ;
		}
		envp = envp->next;
	}
	if (ftcd_c(cmd) == UNSUCCESSFUL)
		return (UNSUCCESSFUL);
	return (SUCCESSFUL);
}

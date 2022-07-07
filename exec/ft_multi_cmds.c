/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:17:14 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/07 15:38:22 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_builtin_1(t_cmdl *list, struct s_envp *envp)
{
	char	**argv;

	if (ft_strncmp("echo", list[list->cmd_iteration].cmd, 5) == 0)
	{
		argv = create_argv_for_execve(list);
		execve("builtins_bin/ftecho", argv, envp->environment);
		exit(127);
	}
	else if (ft_strncmp("cd", list[list->cmd_iteration].cmd, 3) == 0)
	{
		argv = create_argv_for_execve(list);
		execve("builtins_bin/ftcd", argv, envp->environment);
		exit(31);
	}
	else if (ft_strncmp("exit", list[list->cmd_iteration].cmd, 5) == 0)
	{
		argv = create_argv_for_execve(list);
		execve("builtins_bin/ftexit", argv, envp->environment);
		exit(127);
	}
	else if (ft_strncmp("pwd", list[list->cmd_iteration].cmd, 4) == 0)
	{
		argv = create_argv_for_execve(list);
		execve("builtins_bin/ftpwd", argv, envp->environment);
		exit(127);
	}
	return (0);
}

int	set_rd( t_cmdl *list)
{
	int	i;

	i = 0;
	while ( i < list->count_redire)
	{
		if (ft_strncmp(list[list->cmd_iteration].type[i], ">", 2) == 0)
			dup2(list->fd_out, 1);
		if (ft_strncmp(list[list->cmd_iteration].type[i], "<", 2) == 0)
			dup2(list->fd_in, 0);
		if (ft_strncmp(list[list->cmd_iteration].type[i], ">>", 3) == 0)
			dup2(list->fd_out, 1);
		if (ft_strncmp(list[list->cmd_iteration].type[i], ">", 2) == 0)
			close(list->fd_out);
		if (ft_strncmp(list[list->cmd_iteration].type[i], "<", 2) == 0)
			close(list->fd_in);
		if (ft_strncmp(list[list->cmd_iteration].type[i],  ">>", 3) == 0)
			close(list->fd_out);
		i++;
	}
	return (0);
}


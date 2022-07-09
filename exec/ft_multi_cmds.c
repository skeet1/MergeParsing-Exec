/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:17:14 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/09 07:31:00 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_builtin_1(t_cmd *list, struct s_envp *envp)
{
	// char	**argv;

	// if (ft_strncmp("echo", list[list->cmd_iteration].cmd, 5) == 0)
	// {
	// 	argv = create_argv_for_execve(list);
	// 	execve("builtins_bin/ftecho", argv, envp->environment);
	// 	exit(127);
	// }
	// else if (ft_strncmp("cd", list[list->cmd_iteration].cmd, 3) == 0)
	// {
	// 	argv = create_argv_for_execve(list);
	// 	execve("builtins_bin/ftcd", argv, envp->environment);
	// 	exit(31);
	// }
	// else if (ft_strncmp("exit", list[list->cmd_iteration].cmd, 5) == 0)
	// {
	// 	argv = create_argv_for_execve(list);
	// 	execve("builtins_bin/ftexit", argv, envp->environment);
	// 	exit(127);
	// }
	// else if (ft_strncmp("pwd", list[list->cmd_iteration].cmd, 4) == 0)
	// {
	// 	argv = create_argv_for_execve(list);
	// 	execve("builtins_bin/ftpwd", argv, envp->environment);
	// 	exit(127);
	// }
	return (0);
}

int	set_rd( t_cmd *list)
{
	int	i;

	i = 0;
	while (list->f_type[i])
	{
		if (list->f_type[i] == RED_OUT)
			dup2(list->fd_out, 1);
		if (list->f_type[i] == RED_IN)
			dup2(list->fd_in, 0);
		if (list->f_type[i] == RED_OUT_APP)
			dup2(list->fd_out, 1);
		if (list->f_type[i] == RED_OUT)
			close(list->fd_out);
		if (list->f_type[i] == RED_IN)
			close(list->fd_in);
		if (list->f_type[i] == RED_OUT_APP)
			close(list->fd_out);
		i++;
	}
	return (0);
}


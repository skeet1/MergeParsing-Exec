/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 07:40:08 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/16 21:54:53 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parse.h"
#include "../libft/libft.h"


void	dupandclose(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds->f_type[i])
	{
		if (cmds->f_type[i] == RED_IN_APP)
			dup2(cmds->fd_in, 0);
		if (cmds->f_type[i] == RED_OUT)
			dup2(cmds->fd_out, 1);
		if (cmds->f_type[i] == RED_IN)
			dup2(cmds->fd_in, 0);
		if (cmds->f_type[i] == RED_OUT_APP)
			dup2(cmds->fd_out, 1);
		if (cmds->f_type[i] == RED_OUT)
			close(cmds->fd_out);
		if (cmds->f_type[i] == RED_IN)
			close(cmds->fd_in);
		if (cmds->f_type[i] == RED_IN_APP)
			close(cmds->fd_in);
		i++;
	}
}

int	one_cmd_1( t_lis	*envp, t_cmd *cmds)
{
	int	i;

	i = 0;
	if (fork() == 0)
	{
		if (redirections(cmds) == 3)
			exit(1);
		heredoc_exec(cmds);
		dupandclose(cmds);
		ft_bin_usr_sbin(cmds, envp);
	}
	else
	{
		wait(&g_exit_status);
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		i = 0;
	}
	return (g_exit_status);
}

void	closefd(t_cmd *cmds)
{
	int	i;

	i = 0;
	if (cmds->f_type != NULL)
	{
		if (cmds->f_type[i] == RED_OUT)
		{
			close(cmds->fd_out);
		}
		if (cmds->f_type[i] == RED_IN)
		{
			close(cmds->fd_in);
		}
		if (cmds->f_type[i] == RED_OUT_APP)
		{
			close(cmds->fd_out);
		}
	}
}

int	noargs( t_lis	*envp, t_cmd *cmds)
{
	int	i;

	i = 0;
	if (redirections(cmds) == 3)
		return (3);
	heredoc_exec(cmds);
	closefd(cmds);
	return (0);
}

int	one_cmd( t_lis	*envp, t_cmd *cmds)
{

	if (cmds->cmd[0] == NULL)
	{
		noargs(envp, cmds);
		return (1);
	}
	else if (cmds->cmd[0])
	{
		if (is_builtin(cmds) == 0)
		{
			if (redirections(cmds) == 3)
				return (3);
			heredoc_exec(cmds);
			ft_is_built_in(envp, cmds);
			closefd(cmds);
			return (1);
		}
		else if (is_builtin(cmds) == 3)
		{
			one_cmd_1(envp, cmds);
			return (1);
		}
	}
	return (0);
}

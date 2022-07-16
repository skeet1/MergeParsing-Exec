/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 07:40:08 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/16 16:30:42 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parse.h"

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

int	one_cmd_1(struct s_environ *environ, t_cmd *cmds)
{
	int	i;

	i = 0;
	if (fork() == 0)
	{
		if (redirections(cmds) == 3)
			exit(1);
		heredoc_exec(cmds);
		dupandclose(cmds);
		ft_bin_usr_sbin(cmds, environ);
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

int	noargs(struct s_environ *environ, t_cmd *cmds)
{
	int	i;

	i = 0;
	(void)environ;
	if (redirections(cmds) == 3)
		return (3);
	heredoc_exec(cmds);
	closefd(cmds);
	return (0);
}

int	one_cmd(struct s_environ *environ, t_cmd *cmds)
{
	if (cmds->cmd[0] == NULL)
	{
		noargs(environ, cmds);
		return (1);
	}
	else if (cmds->cmd[0])
	{
		if (is_builtin(cmds) == 0)
		{
			if (redirections(cmds) == 3)
				return (3);
			heredoc_exec(cmds);
			ft_is_built_in(environ, cmds);
			closefd(cmds);
			return (1);
		}
		else if (is_builtin(cmds) == 3)
		{
			one_cmd_1(environ, cmds);
			return (1);
		}
	}
	return (0);
}

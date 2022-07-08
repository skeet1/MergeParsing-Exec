/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 07:40:08 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/08 21:36:04 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parse.h"
int	one_cmd_1(t_cmdl *list, struct s_envp *envp, t_token *token, t_cmd *cmds)
{
	int	i;

	i = 0;
	if (fork() == 0)
	{
		if (redirections(cmds, token) == 3)
			return (3);
		heredoc_without_cmd(list);
		while (i < list->count_redire)
		{
			if (ft_strncmp(list[0].type[i], "<<", 3) == 0)
				dup2(list->fd_in, 0);
			if (ft_strncmp(list[0].type[i], ">", 2) == 0)
				dup2(list->fd_out, 1);
			if (ft_strncmp(list[0].type[i], "<", 2) == 0)
				dup2(list->fd_in, 0);
			if (ft_strncmp(list[0].type[i], ">>", 3) == 0)
				dup2(list->fd_out, 1);
			if (ft_strncmp(list[0].type[i], ">", 2) == 0)
				close(list->fd_out);
			if (ft_strncmp(list[0].type[i], "<", 2) == 0)
				close(list->fd_in);
			if (ft_strncmp(list[0].type[i], "<<", 3) == 0)
				close(list->fd_in);
			i++;
		}
		ft_bin_usr_sbin(list, envp);
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

int	one_cmd(struct s_envp *envp,t_token *token, t_cmd *cmds)
{
	int	i;
	int	x;

	if (cmds->cmdnbr == 1 && is_builtin(cmds, 0) == 0)
	{
		i = 0;
		if (redirections(cmds, token) == 3)
			return (3);
		ft_is_built_in(envp, cmds);
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
		return (1);
	}
	else if (cmd->cmd_nbr == 1 && is_builtin(cmd, 0) == 3)
	{

		one_cmd_1(cmd, envp, token, cmds);
		return (1);
	}
	return (0);
}

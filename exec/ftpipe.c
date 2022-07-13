/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 08:51:00 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/13 07:05:22 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parse.h"

int	ft_pipe_c(t_cmd *list, struct s_envp *envp, int fdin, int *pipes)
{
	dup2(fdin, 0);
	if (list->next)
		dup2(pipes[1], 1);
	close(pipes[0]);
	if (redirections(list) == 3)
	{
		g_exit_status = 1;
		return (1);
	}
	set_rd(list);
	if (ft_is_built_in(envp, list) == 1)
	{
		exit(1);
	}
	ft_bin_usr_sbin(list, envp);
	return (0);
}

int	ft_pipe_wait(t_cmd *list, struct s_envp *envp, int g)
{
	wait(&g_exit_status);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	while (g)
	{
		wait(NULL);
		g--;
	}
	return (0);
}

int	ft_pipe_rd(t_cmd *list, struct s_envp *envp, int *pipes)
{
	if (heredoc_exec(list) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pipe(pipes) < 0)
		return (1);
	return (0);
}

int	ft_pipe(t_cmd *list, struct s_envp *envp)
{
	int	id;
	int	pipes[2];
	int	fdin;
	int	g;
	int	i;

	list->fd_out = 1;
	g = 0;
	i = 0;
	fdin = 0;
	while (list)
	{
		ft_pipe_rd(list, envp, pipes);
		id = fork();
		g++;
		if (id == 0)
			ft_pipe_c(list, envp, fdin, pipes);
		close(pipes[1]);
		fdin = pipes[0];
		list = list->next;
	}
	ft_pipe_wait(list, envp, g);
	return (0);
}

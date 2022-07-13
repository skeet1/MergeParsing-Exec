/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 08:51:00 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/13 21:07:04 by atabiti          ###   ########.fr       */
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
		exit(1);
	}
	set_rd(list);
	if (ft_is_built_in(envp, list) == 1)
	{
		exit(1);
	}
	ft_bin_usr_sbin(list, envp);
}

int	ft_pipe_wait(int g)
{
	wait(&g_exit_status);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	while (g)
	{
		wait(NULL);
		g--;
	}
}

int	ft_pipe_rd(t_cmd *list, int *pipes)
{
	// if (heredoc_exec(list) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	if (pipe(pipes) < 0)
	{
		perror("Minishell: ");
		g_exit_status = 1;
		return (EXIT_FAILURE);
	}
	return (0);
}

int	savefdin(t_cmd *list, int *pipes, int fdin)
{
	close(pipes[1]);
	fdin = pipes[0];
	return (fdin);
}

int	ft_pipe(t_cmd *list, struct s_envp *envp)
{
	int	id;
	int	pipes[2];
	int	fdin;
	int	g;

	fdin = 0;
	list->fd_out = 1;
	g = 0;
	if (heredoc_exec(list) == UNSUCCESSFUL)
		return (UNSUCCESSFUL);
	while (list)
	{
		if(ft_pipe_rd(list, pipes) == UNSUCCESSFUL)
		return UNSUCCESSFUL;
		id = fork();
				g++;
		if (id == -1)
		{
			perror("Minishell: ");
			return (1);
		}
		if (id == 0)
			ft_pipe_c(list, envp, fdin, pipes);
		fdin = savefdin(list, pipes, fdin);
		list = list->next;
	}
	ft_pipe_wait(g);
}

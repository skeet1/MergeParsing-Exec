/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 08:51:00 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/12 10:38:38 by atabiti          ###   ########.fr       */
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
	redirections(list);
	set_rd(list);
	if (ft_is_built_in(envp, list) == 1)
	{
		exit(1);
	}
	ft_bin_usr_sbin(list, envp);
}

int	ft_pipe(t_cmd *list, struct s_envp *envp)
{
	int	id;
	int	pipes[2];
	int	fdin;
	int	g;
	int	i;

	g = 0;
	i = 0;
	fdin = 0;
	while (list)
	{
		heredoc_exec(list);
		if (pipe(pipes) < 0)
			return (0);
		id = fork();
								g++;

		if (id == 0)
		{
						ft_pipe_c(list, envp, fdin, pipes);

		}
		else
		{
			// wait(&g_exit_status);
			// if (WIFEXITED(g_exit_status))
			// 	g_exit_status = WEXITSTATUS(g_exit_status);
			close(pipes[1]);
			fdin = pipes[0];
			list = list->next;
		}
	}
	printf(" g is %d\n", g);
	wait(&g_exit_status);
			if (WIFEXITED(g_exit_status))
				g_exit_status = WEXITSTATUS(g_exit_status);
	while(g)
	{
		wait(NULL);
		g--;
	}
	
}

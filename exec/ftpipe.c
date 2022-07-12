/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 08:51:00 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/12 09:25:25 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parse.h"
// problem here
//&& redire_2(list) == 0 i must check previous redirection is not rdout
//  &&  ft_strncmp( list[0].type[1], RDOUT, 7) != 0 not workings
//check echo asd > f1 > f3 << f4
//ls > f1 > f2<< FF

int	ft_pipe_c(t_cmd *list, struct s_envp *envp, int fdin, int *pipes)
{
	// if(i != 0)
	dup2(fdin, 0);
	if (list->next)
		dup2(pipes[1], 1); //
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
	int	i;
	int	id;
	int	pipes[2];
	int	fdin;

	i = 0;
	fdin = 0;
	list->cmd_iteration = 0;
	list->fd_out = 1;
	while (list)
	{
		heredoc_exec(list);
		if (pipe(pipes) < 0)
			return (0);
		id = fork();
		if (id == 0)
		{
			ft_pipe_c(list, envp, fdin, pipes);
		}
		else
		{
			wait(&g_exit_status);
			if (WIFEXITED(g_exit_status))
				g_exit_status = WEXITSTATUS(g_exit_status);
			close(pipes[1]);
			fdin = pipes[0];
			i++;
			list = list->next;
		}
	}
}

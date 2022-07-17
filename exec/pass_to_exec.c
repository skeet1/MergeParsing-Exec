/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:34:10 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/17 11:22:10 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "../parsing/parse.h"

void	handler2(int sig)
{
	if (sig == SIGINT)
		printf("\n");
}

int	count_cmds(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}

int	pass_to_exec(t_lis *envp, t_cmd *cmds)
{
	int	nbr;
	int	id;
	int	fd_in;

	id = 0;
	fd_in = 0;
	ft_init(cmds);
	nbr = count_cmds(cmds);
	cmds->cmdnbr = nbr;
	signal(SIGINT, handler2);
	if (nbr == 1)
	{
		one_cmd(envp, cmds);
	}
	else if (cmds->cmdnbr > 1)
	{
		ft_pipe(cmds, envp, id, fd_in);
	}
	return (0);
}

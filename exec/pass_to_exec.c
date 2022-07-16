/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:34:10 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/16 08:23:16 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parse.h"

int	ft_lstsize(t_cmd *lst)
{
	int	lstlen;

	lstlen = 0;
	while (lst)
	{
		lst = lst->next;
		lstlen++;
	}
	return (lstlen);
}

void	handler2(int sig)
{
	if (sig == SIGINT)
		printf("\n");
}

int	pass_to_exec(struct s_environ *environ, t_cmd *cmds)
{
	int	nbr;
	int	id;
	int	fd_in;

	fd_in = 0;
	print_cmd(cmds);
	ft_init(cmds, environ);
	nbr = ft_lstsize(cmds);
	cmds->cmdnbr = nbr;
	signal(SIGINT, handler2);
	if (nbr == 1)
	{
		one_cmd(environ, cmds);
	}
	else if (cmds->cmdnbr > 1)
	{
		ft_pipe(cmds, environ, id, fd_in);
	}
	return (0);
}

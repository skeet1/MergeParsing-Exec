/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:34:10 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/16 23:18:05 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

#include "../parsing/parse.h"



void	handler2(int sig)
{
	if (sig == SIGINT)
		printf("\n");
}

int ft_ll(t_cmd *cmds)
{
	int i = 0 ;
	while(cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return i;
}

int	pass_to_exec( t_lis	*envp, t_cmd *cmds)
{
	int	nbr;
	int	id;
	int	fd_in;

	id = 0;
	fd_in = 0;
	// print_cmd(cmds);
	ft_init(cmds, envp);
	
	nbr = ft_ll(cmds);				

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

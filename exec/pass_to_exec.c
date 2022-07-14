/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:34:10 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/14 10:11:04 by atabiti          ###   ########.fr       */
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

int	pass_to_exec(struct s_envp *envp, t_cmd *cmds)
{
	int	nbr;

	print_cmd(cmds);
	ft_init(cmds, envp);
	nbr = ft_lstsize(cmds);
	cmds->cmdnbr = nbr;
	if (nbr == 1)
	{
		one_cmd(envp, cmds);
	}
	else if (cmds->cmdnbr > 1)
	{
		ft_pipe(cmds, envp);
	}
	return (0);
}

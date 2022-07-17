/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 08:43:04 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/16 21:51:19 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"


int	ft_init(t_cmd *cmds, t_lis	*envp)
{
	cmds->cmdnbr = 0;
	cmds->new = NULL;
	cmds->cmdnbr = 0;
	cmds->cmd_iteration = 0;
	cmds->envvarpos = 0;
	cmds->delimiter = NULL;
	cmds->fd_out = 1;
	return (0);
}

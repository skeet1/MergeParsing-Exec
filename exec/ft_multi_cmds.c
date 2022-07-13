/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:17:14 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/13 11:50:07 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_rd(t_cmd *list)
{
	int	i;

	i = 0;
	while (list->f_type[i])
	{
		if (list->f_type[i] == RED_OUT)
			dup2(list->fd_out, 1);
		if (list->f_type[i] == RED_IN_APP)
			dup2(list->fd_in, 0);
		if (list->f_type[i] == RED_IN)
			dup2(list->fd_in, 0);
		if (list->f_type[i] == RED_OUT_APP)
			dup2(list->fd_out, 1);
		if (list->f_type[i] == RED_OUT)
			close(list->fd_out);
		if (list->f_type[i] == RED_IN)
			close(list->fd_in);
		if (list->f_type[i] == RED_OUT_APP)
			close(list->fd_out);
		if (list->f_type[i] == RED_IN_APP)
			close(list->fd_in);
		i++;
	}
	list->fd_out = 1;
	return (0);
}

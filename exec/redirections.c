/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:50:59 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/13 06:55:37 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parse.h"

int	redirections_c(t_cmd *list, int i)
{
	if (list->f_type[i] == RED_IN)
	{
		list->fd_in = open(list->f_name[i], O_RDONLY, 0);
		if (list->fd_in == -1)
		{
			printf("Minishell: No such file or directory\n");
			return (3);
		}
	}
	if (list->f_type[i] == RED_OUT_APP)
	{
		list->fd_out = open(list->f_name[i], O_RDWR | O_CREAT | O_APPEND, 0600);
	}
	if (list->f_type[i] == RED_IN_APP)
	{
		list->fd_in = open("/tmp/tmpherdoc", O_RDONLY);
	}
	return (0);
}

int	redirections(t_cmd *list)
{
	int	i;

	i = 0;
	while (list->f_type[i])
	{
		if (list->f_type[i] == RED_OUT)
		{
			list->fd_out = open(list->f_name[i], O_RDWR | O_CREAT | O_TRUNC,
					0600);
			if (list->fd_out == -1)
			{
				printf("Minishell: No such file or directory\n");
				return (3);
			}
		}
		if (redirections_c(list, i) == 3)
			return (3);
		i++;
	}
	return (0);
}

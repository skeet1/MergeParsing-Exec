/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:50:22 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/16 13:21:34 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	ft_env(struct s_environ *environ, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (environ != NULL)
	{
		if (environ->value != NULL && environ->name)
			ft_putendl_fd(environ->env, cmd->fd_out);
		environ = environ->next;
	}
	return (0);
}

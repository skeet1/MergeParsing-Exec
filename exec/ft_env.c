/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:50:22 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/15 13:46:15 by atabiti          ###   ########.fr       */
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
		if (environ->value != NULL)
			ft_putendl_fd(environ->env, cmd->fd_out);
		environ = environ->next;
	}
	return (0);
}

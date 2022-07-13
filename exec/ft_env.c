/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:50:22 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/13 11:17:29 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	ft_env(struct s_envp *envp, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < envp->envpitems)
	{
		if (envp->value[i] != NULL)
			ft_putendl_fd(envp->environment[i], cmd->fd_out);
		i++;
	}
	return (0);
}

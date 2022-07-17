/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:50:22 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/17 07:10:12 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	ft_env(t_lis *envp, t_cmd *cmd)
{
	int		i;
	t_env	*envval;

	i = 0;
	envp = envp->next;
	while (envp != NULL)
	{
		envval = envp->content;
		if (envval->value != NULL)
		{
			ft_putstr_fd(envval->name, cmd->fd_out);
		ft_putstr_fd("=", cmd->fd_out);
		ft_putendl_fd(envval->value, cmd->fd_out);
		}
			
		envp = envp->next;
	}
	return (0);
}

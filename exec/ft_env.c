/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:50:22 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/17 09:16:06 by atabiti          ###   ########.fr       */
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
		if (ft_strlen(envval->value) != 0)
		{
			ft_putstr_fd(envval->name, cmd->fd_out);
			ft_putstr_fd("=", cmd->fd_out);
			ft_putendl_fd(envval->value, cmd->fd_out);
		}
		envp = envp->next;
	}
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 90 && c <= 122))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:50:22 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/13 09:00:14 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	ft_env(struct s_envp *envp)
{
	int	i;

	i = 0;
	while (i < envp->envpitems)
	{
		if (envp->value[i] != NULL)
			ft_putendl_fd(envp->environment[i], 1);
		i++;
	}
	return (0);
}

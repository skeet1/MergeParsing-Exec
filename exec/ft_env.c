/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:50:22 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/11 22:43:05 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

int	ft_env(struct s_envp *envp, t_cmd *list)
{
	int	i;

	i = 0;
	while (i < envp->envpitems)
	{
		if(envp->value[i] != NULL  )
		ft_putendl_fd(envp->environment[i],1);
		i++;
	}
	return (0);
}

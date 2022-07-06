/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:50:22 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/04 18:36:31 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

int	ft_env(struct s_envp *envp, t_cmdl *list)
{
	int	i;

	i = 0;
	while (i < envp->envpitems)
	{
		if(envp->value[i] != NULL  )
		ft_putendl_fd(envp->environment[i], list->fd_out);
		i++;
	}
	return (1);
}

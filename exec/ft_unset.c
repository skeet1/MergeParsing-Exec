/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:15:57 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/17 08:28:21 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	ft_equal_sign(t_cmd *list, int arg)
{
	int	i;

	i = 0;
	while (list->cmd[arg][i])
	{
		if (list->cmd[arg][i] == '=')
		{
			printf("Minishell: unset: `%s': not a valid identifier\n",
				list->cmd[arg]);
			return (UNSUCCESSFUL);
		}
		i++;
	}
	return (SUCCESSFUL);
}

int	ft_unset(t_lis *envp, t_cmd *list, int arg)
{
	t_env	*pre;
	t_lis	*tmp;

	tmp = envp;
	envp = tmp->next;
	while (envp)
	{
		pre = envp->content;
		if (ft_strncmp(pre->name, list->cmd[arg], ft_strlen(list->cmd[arg])
				+ 1) == 0)
		{
			tmp->next = envp->next;
			free(pre->name);
			free(pre->value);
			free(pre);
			free(envp);
		}
		else
			tmp = tmp->next;
		envp = tmp->next;
	}
	return (SUCCESSFUL);
}

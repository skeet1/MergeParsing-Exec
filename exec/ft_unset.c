/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:15:57 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/15 20:32:15 by mkarim           ###   ########.fr       */
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

int	unsett(struct s_environ **head, int pos, char *arg)
{
	struct s_environ	*tmp;
	struct s_environ	*prev;
	int					x;

	tmp = *head;
	prev = *head;
	if (*head == NULL)
		return (1);
	if (ft_strncmp(tmp->name, arg, ft_strlen(arg)) == 0)
	{
		*head = tmp->next;
		return (SUCCESSFUL);
	}
	while (tmp)
	{
		if (ft_strncmp(tmp->name, arg, ft_strlen(arg)) == 0)
		{
			prev->next = tmp->next;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (SUCCESSFUL);
}

int	ft_unset(struct s_environ *environ, t_cmd *list, int arg)
{
	int					pos;
	pos = 1;
	unsett(&environ, pos, list->cmd[arg]);
	return (SUCCESSFUL);
}

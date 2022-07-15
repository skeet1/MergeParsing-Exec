/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:15:57 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/15 14:09:17 by atabiti          ###   ########.fr       */
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

int	unsett(struct s_environ **head, int pos, char *argg)
{
	struct s_environ	*current;
	struct s_environ	*previous;
	int					x;

	current = *head;
	previous = *head;
	if (*head == NULL)
		return (1);
	x = 0;
	while (current)
	{
		if (ft_strncmp(argg, current->name, ft_strlen(current->name) + 1) == 0)
		{
			previous->next = current->next;
			free(current);
			current = NULL;
			return (0);
		}
		previous = current;
		current = current->next;
		x++;
	}
	return (SUCCESSFUL);
}

int	ft_unset(struct s_environ *environ, t_cmd *list, int arg)
{
	int					pos;
	struct s_environ	*tmp;

	pos = 1;
	tmp = environ;
	unsett(&environ, pos, list->cmd[arg]);
	return (SUCCESSFUL);
}

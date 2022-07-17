/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_equal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:30:09 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/17 08:48:17 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	free_environ(struct s_environ **head)
{
	struct s_environ	*c;

	c = *head;
	while (c != NULL)
	{
		if (c->value)
			free(c->value);
		if (c->name)
			free(c->name);
		if (c->env)
			free(c->env);
		c = c->next;
	}
}

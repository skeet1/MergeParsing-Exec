/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_equal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:30:09 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/16 08:28:07 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	ft_export_no_equal(struct s_environ *envp, t_cmd *cmd, int i)
{
	int					x;
	struct s_environ	*tmp;

	tmp = envp;
	x = 0;
	if (check_name_is_valid(&cmd->cmd[i], i, cmd) == 1)
		return (UNSUCCESSFUL);
	while (tmp)
	{
		if (ft_strncmp(tmp->name, cmd->cmd[i], ft_strlen(cmd->cmd[i]) + 1) == 0)
		{
			printf(" name %s    args to export %s\n", tmp->name, cmd->cmd[i]);
			return (SUCCESSFUL);
		}
		tmp = tmp->next;
	}
	ftaddback(&envp, cmd->cmd[i]);
	return (SUCCESSFUL);
}

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

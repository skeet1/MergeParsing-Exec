/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_equal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:30:09 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/16 23:55:09 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	ft_export_no_equal(t_lis *envp, t_cmd *cmd, int i)
{
// 	int		x;
// 	t_env	*en;
// 	t_lis	*tmp;
// 	char	*name;
// 	char	*value;

// 	tmp = envp;
// 	// name = envname(cmd->cmd[i]);
// 	// value = envname(cmd->cmd[i]);
// 	x = 0;
// 	if (check_name_is_valid(&cmd->cmd[i], i, cmd) == 1)
// 		return (UNSUCCESSFUL);
// 	while (envp != NULL)
// 	{
// 		en = envp->content;
// 		if (ft_strncmp(en->name, cmd->cmd[i], ft_strlen(cmd->cmd[i]) + 1) == 0)
// 		{
// 			return (SUCCESSFUL);
// 		}
// 		tmp = envp;
// 		envp = envp->next;
// 	}
// 	en = new_node(name, value);
// 	tmp->next = ft_lstnew(en);
// 	free(name);
// 	free(value);
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

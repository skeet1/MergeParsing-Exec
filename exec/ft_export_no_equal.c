/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_equal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:30:09 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/17 09:50:50 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	free_environ(t_lis *head)
{
	t_env	*env;

	head = head->next;
	while (head != NULL)
	{
		env = head->content;
		if (env->value)
			free(env->value);
		if (env->name)
			free(env->name);
		head = head->next;
	}
	free(env);
	free(head);
}

int	valid_identifier(t_lis *envp, t_cmd *cmd, int i)
{
	(void)envp;
	if (cmd->cmd[i][0] == '=')
	{
		printf("Minishell: export: `%s': not a valid identifier\n",
			cmd->cmd[i]);
		return (UNSUCCESSFUL);
	}
	return (SUCCESSFUL);
}

char	*extractvalue(t_cmd *cmd, int i)
{
	char	*value;
	int		x;

	value = NULL;
	x = 0;
	while (cmd->cmd[i][x] != '=' && cmd->cmd[i][x] != '\0')
	{
		if (cmd->cmd[i][x] == '=')
			break ;
		x++;
	}
	value = ft_substr(cmd->cmd[i], x + 1, ft_strlen(cmd->cmd[i]) - x);
	return (value);
}

char	*extractname(t_cmd *cmd, int i)
{
	char	*name;
	int		x;

	x = 0;
	while (cmd->cmd[i][x] != '=' && cmd->cmd[i][x] != '\0')
	{
		if (cmd->cmd[i][x] == '=')
			break ;
		x++;
	}
	name = ft_substr(cmd->cmd[i], 0, x);
	return (name);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:26:24 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/17 13:26:37 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	freeit(char *name, char *value)
{
	free(name);
	free(value);
}

int	check_name_is_valid(char *split, int i, t_cmd *cmd)
{
	int	x;

	if (ft_is_alpha_mod(split[0]) == 0)
	{
		printf("Minishell: export: `%s': not a valid identifier\n",
			cmd->cmd[i]);
		return (1);
	}
	x = 1;
	while (split[x])
	{
		if (ft_is_alpha_mod(split[x]) == 0 && ft_isalnum(split[x]) == 0)
		{
			printf("Minishell: export: `%s': not a valid identifier\n",
				cmd->cmd[i]);
			return (1);
		}
		x++;
	}
	return (0);
}

void	modify(t_lis *envp, t_cmd *cmd, int i, char *name)
{
	t_env	*en;
	t_lis	*tmp;
	char	*value;

	value = extractvalue(cmd, i);
	while (envp != NULL)
	{
		en = envp->content;
		if (ft_strncmp(en->name, name, ft_strlen(name) + 1) == 0
			&& value != NULL)
		{
			free(en->value);
			en->value = value;
		}
		if (ft_strncmp(en->name, name, ft_strlen(name) + 1) == 0)
			return ;
		tmp = envp;
		envp = envp->next;
	}
	en = new_node(name, value);
	tmp->next = ft_lstnew(en);
	free(value);
}

int	ft_export(t_lis *envp, t_cmd *cmd, int i)
{
	char	*name;

	name = extractname(cmd, i);
	if (check_name_is_valid(name, i, cmd) == 1 && name != NULL)
	{
		free(name);
		return (UNSUCCESSFUL);
	}
	modify(envp, cmd, i, name);
	return (SUCCESSFUL);
}

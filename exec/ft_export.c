/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:26:24 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/17 09:03:36 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	modify_name(t_lis *envp, t_cmd *cmd, char **split, int i)
{
	int		t;
	t_env	*envval;

	t = 0;
	envp = envp->next;
	while (envp)
	{
		envval = envp->content;
		if (ft_strncmp(envval->name, split[0], ft_strlen(split[0]) + 1) == 0)
		{
			while (cmd->cmd[i][t])
			{
				if (cmd->cmd[i][t] == '=')
				{
					free(envval->name);
					envval->name = cmd->cmd[i];
					return (0);
				}
				t++;
			}
			t = 0;
		}
		envp = envp->next;
	}
	return (1);
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

char	*extractvalue(t_lis *envp, t_cmd *cmd, int i)
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
char	*extractname(t_lis *envp, t_cmd *cmd, int i)
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

int	ft_export(t_lis *envp, t_cmd *cmd, int i)
{
	int		x;
	t_env	*en;
	t_lis	*tmp;
	char	*name;
	char	*value;

	if (valid_identifier(envp, cmd, i) == UNSUCCESSFUL)
		return (UNSUCCESSFUL);
	value = extractvalue(envp, cmd, i);
	name = extractname(envp, cmd, i);
	if(check_name_is_valid(name, i , cmd) == 1 && name != NULL)
	return (1);
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
			return (SUCCESSFUL);
		tmp = envp;
		envp = envp->next;
	}
	en = new_node(name, value);
	tmp->next = ft_lstnew(en);
	freeit(name, value);
	return (SUCCESSFUL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envfill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:51:47 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/16 23:50:01 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

t_env	*new_node(char *name, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = NULL;
	new->value = NULL;
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	return (new);
}

t_lis	*copyenv(t_lis *env_clone, char **env)
{
	t_lis	*new;
	t_env	*temp;
	char	*name;
	char	*value;
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (env[i])
	{
		if (!(ft_strchr(env[i], '=')))
		{
			name = env[i];
			value = ft_strdup("");
		}
		else
		{
			while (env[i][x] != '=' && env[i][x] != '\0')
			{
				if (env[i][x] == '=')
					break ;
				x++;
			}
			name = ft_substr(env[i], 0, x);
			value = ft_substr(env[i], x + 1, ft_strlen(env[i]) - x);
			x = 0;
		}
		temp = new_node(name, value);
		new = ft_lstnew(temp);
		ft_lstadd_back(&env_clone, new);
		free(name);
		free(value);
		i++;
	}
	return (env_clone);
}

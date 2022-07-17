/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envfill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:51:47 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/17 11:14:54 by atabiti          ###   ########.fr       */
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

char	*ft_value(char *env)
{
	char	*value;
	int		x;

	x = 0;
	while (env[x] != '=' && env[x] != '\0')
	{
		if (env[x] == '=')
			break ;
		x++;
	}
	value = ft_substr(env, x + 1, ft_strlen(env) - x);
	return (value);
}

char	*ft_name(char *env)
{
	char	*name;
	int		x;

	x = 0;
	while (env[x] != '=' && env[x] != '\0')
	{
		if (env[x] == '=')
			break ;
		x++;
	}
	name = ft_substr(env, 0, x);
	return (name);
}

t_lis	*copyenv(t_lis *env_clone, char **env)
{
	t_lis	*new;
	t_env	*temp;
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (env[i])
	{
		if (!(ft_strchr(env[i], '=')))
		{
			name = env[i];
			value = ft_strdup("");
		}
		else
		name = ft_name(env[i]);
		value = ft_value(env[i]);
		temp = new_node(name, value);
		new = ft_lstnew(temp);
		ft_lstadd_back(&env_clone, new);
		freeit(name, value);
		i++;
	}
	return (env_clone);
}

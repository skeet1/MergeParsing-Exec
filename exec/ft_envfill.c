/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envfill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:51:47 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/14 16:19:31 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

struct					s_environ
{
	char				*env;
	char				*name;
	char				*value;
	struct s_environ	*next;
};

struct s_environ	*ft_new_node(char *envv, char *name, char *value)
{
	struct s_environ	*new;

	new = (struct s_environ *)malloc(sizeof(struct s_environ));
	if (!new)
		return (new);
	new->value = value;
	new->name = name;
	new->env = envv;
	new->next = NULL;
	return (new);
}

void	ft_add_back(struct s_environ **token, char *envv, char *name,
		char *value)
{
	struct s_environ	*last;
	struct s_environ	*new;

	last = *token;
	new = ft_new_node(envv, name, value);
	if (new == NULL)
		return ;
	if (last == NULL)
	{
		*token = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
}

int	ft_split_env_next(struct s_environ *envp, char **en, int i)
{
	int	x;

	x = 0;
	i = 0;
	while (envp)
	{
		while (envp->env[x] != '=' && envp->env[x] != '\0')
		{
			if (envp->env[x] == '=')
				break ;
			x++;
		}
		envp->name = ft_substr(envp->env, 0, x);
		envp->value = ft_substr(envp->env, x + 1, ft_strlen(envp->env) - x);
		x = 0;
		envp = envp->next;
	}
	return (0);
}

void	print(struct s_environ *env, char **envp)
{
	ft_split_env_next(env, envp, 0);
	while (env)
	{
		printf("%s |  %s \n", env->name, env->value);
		env = env->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	struct s_environ *env;
	int i = 0;
	env = NULL;

	int x = 0;
	while (envp[i])
	{
		ft_add_back(&env, envp[i], NULL, NULL);
		i++;
	}
	print(env, envp);
	return (0);
}
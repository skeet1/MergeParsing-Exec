/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envfill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:51:47 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/14 21:45:50 by atabiti          ###   ########.fr       */
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
// int	ft_unsett(struct s_environ **env, char *un)
// {
// 	struct s_environ	*tmp;
// 	struct s_environ	*prev;

// 	tmp = *env;
// 	prev = *env;
// 	if (tmp)
// 	{
// 		if (ft_strcmp(tmp->name, un) == 0)
// 		{
// 			tmp = tmp->next;
// 			free(tmp->env);
// 			free(tmp->name);
// 			free(tmp->next);
// 			return ;
// 		}
// 		prev = tmp;
// 		tmp = tmp->next;
// 	}
// 	while (tmp)
// 	{
// 		if (ft_strcmp(tmp->name, un) == 0)
// 		{
// 			prev->next = tmp->next;
// 			free(tmp->env);
// 			free(tmp->name);
// 			free(tmp->next);
// 			break ;
// 		}
// 		prev = tmp;
// 		tmp = tmp->next;
// 	}
// 	return (SUCCESSFUL);
// }
int	unsett(struct s_environ **head, int pos)
{
	struct s_environ	*current;
	struct s_environ	*previous;

	current = *head;
	previous = *head;
	if (*head == NULL)
		return (1);
	else if (pos == 1)
	{
		*head = current->next;
		free(current);
		current = NULL;
	}
	else
	{
		while (pos != 1)
		{
			previous = current;
			current = current->next;
			pos--;
		}
		previous->next = current->next;
		free(current);
		current = NULL;
	}
	return (SUCCESSFUL);
}

int	ft_eport(struct s_environ *env)
{
	char	**new;
	char	**split;
	int		x;

	ft_add_back(&env, "anas=", NULL, NULL);
	return (SUCCESSFUL);
}

void	print(struct s_environ *env, char **envp)
{
	int					pos;
	struct s_environ	*tmp;

	pos = 1;
	tmp = env;
	ft_eport(env);
	ft_split_env_next(env, envp, 0);
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "SHELL", ft_strlen("SHELL")) == 0)
			break ;
		pos++;
		tmp = tmp->next;
	}
	unsett(&env, pos);
	// unsett(&en, "HOME");
	// unsett(&env, "PWD");
	// unsett(&env, "USER");
	// unsett(&env, "SHLVL");
	// unsett(&env, "VSCODE_IPC_HOOK_CLI");
	// unsett(&env, "OLDPWD");
	// unsett(&env, "NAME");
	// unsett(&env, "XAUTHORITY");
	// unsett(&env, "LANG");
	// // unsett(&env, "LS_COLORS");
	// unsett(&env, "PATH");
	// unsett(&env, "PULSE_SERVER");
	// unsett(&env, "HOSTTYPE");
	while (env)
	{
		// printf("%s |  %s \n", env->name, env->value);
		printf("%s \n", env->env);
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
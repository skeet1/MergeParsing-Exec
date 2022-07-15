/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envfill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:51:47 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/15 23:39:33 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

struct s_environ	*ftnewnode(char *envv)
{
	struct s_environ	*new;

	new = (struct s_environ *)malloc(sizeof(struct s_environ));
	if (!new)
		return (new);
	new->env = envv;
	new->next = NULL;
	return (new);
}

void	ftaddback(struct s_environ **token, char *envv)
{
	struct s_environ	*last;
	struct s_environ	*new;

	last = *token;
	new = ftnewnode(envv);
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

struct s_environ	*ftsplitenv(struct s_environ *environ, int x)
{
	x = 0;
	while (environ != NULL)
	{
		if (!(ft_strchr(environ->env, '=')))
		{
			environ->name = environ->env;
			environ->value = NULL;
		}
		else
		{
			while (environ->env[x] != '=' && environ->env[x] != '\0')
			{
				if (environ->env[x] == '=')
					break ;
				x++;
			}
			environ->name = ft_substr(environ->env, 0, x);
			environ->value = ft_substr(environ->env, x + 1,
					ft_strlen(environ->env) - x);
			x = 0;
		}
		environ = environ->next;
	}
	return (environ);
}


void	increment_shlvl(struct s_environ *envp)
{
	char	*tmp;
	int		nb;
	char	*joined;
	int x = 0;
	while (envp)
	{
		if (ft_strncmp(envp->name, "SHLVL", 6) == 0)
		{
			nb = ft_atoi(envp->value);
			tmp = ft_itoa(nb + 1);
			joined = ft_strjoin("SHLVL=", tmp);
			free(tmp);
			envp->env = joined;
		}
		envp = envp->next;
	}
	ftsplitenv(envp, x);
}

struct s_environ	*ftcopyenv(struct s_environ *environ, char **envp)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (envp[i])
	{
		ftaddback(&environ, envp[i]);
		i++;
	}
	environ->envpitems = i;
	ftsplitenv(environ, x);
	increment_shlvl(environ);
	return (environ);
}

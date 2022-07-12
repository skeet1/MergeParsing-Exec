/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_1st_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:44:48 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/12 19:17:29 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "../parsing/parse.h"

int	ft_split_env_next(struct s_envp *envp, char **env, int i)
{
	int	x;

	x = 0;
	while (env[i][x] != '=' && env[i][x] != '\0')
	{
		if (env[i][x] == '=')
			break ;
		x++;
	}
	envp->name[i] = ft_substr(env[i], 0, x);
	envp->value[i] = ft_substr(env[i], x + 1, ft_strlen(env[i]) - x);
	x = 0;
	return (0);
}

int	ft_split_env(struct s_envp *envp, char **env)
{
	int		i;
	int		x;
	int		len;

	envp->name = (char **)malloc(sizeof(char *) * envp->envpitems + 1);
	envp->value = (char **)malloc(sizeof(char *) * envp->envpitems + 1);
	i = 0;
	x = 0;
	len = 0;
	len = 0;
	while (i < envp->envpitems)
	{
		if (!(strchr(env[i], '=')))
		{
			envp->name[i] = env[i];
			envp->value[i] = NULL;
			i++;
		}
		else
		{
			ft_split_env_next(envp, env, i);
		i++;
		}
	}
	return (0);
}

int	ft_strlenenv(struct s_envp *envp, char **env)
{
	int	len;

	len = 0;
	while (env[len])
	{
		len++;
	}
	envp->envpitems = len;
	return (0);
}

int	ft_copy_env(struct s_envp *envp, char **env)
{
	char	*joined;
	char	*nbb;
	int		x;
	int		nb;

	x = 0;
	while (x < envp->envpitems)
	{
		nb = 0;
		if (ft_strncmp(envp->name[x], "SHLVL", 6) == 0)
		{
			nb = ft_atoi(envp->value[x]);
			nbb = ft_itoa(nb + 1);
			joined = ft_strjoin("SHLVL=", nbb);
			free(nbb);
			envp->environment[x] = joined;
			x++;
		}
		envp->environment[x] = env[x];
		x++;
	}
	envp->environment[x] = NULL;
	return (0);
}

int	ft_copy_1st_env(struct s_envp *envp, char **env)
{
	int	i;

	ft_strlenenv(envp, env);
	envp->environment = malloc(sizeof(char **) * (envp->envpitems + 1));
	ft_split_env(envp, env);
	i = 0;
	ft_copy_env(envp, env);
	return (0);
}

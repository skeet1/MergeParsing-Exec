/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:15:57 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/14 10:02:31 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	ft_equal_sign(t_cmd *list, int arg)
{
	int	i;

	i = 0;
	while (list->cmd[arg][i])
	{
		if (list->cmd[arg][i] == '=')
		{
			printf("Minishell: unset: `%s': not a valid identifier\n",
				list->cmd[arg]);
			return (UNSUCCESSFUL);
		}
		i++;
	}
	return (SUCCESSFUL);
}

int	ft_search_for_variable_in_env(struct s_envp *envp, t_cmd *list, int arg)
{
	int	lenght;
	int	x;
	int	i;

	lenght = ft_strlen(list->cmd[arg]);
	x = 0;
	i = 0;
	while (x < envp->envpitems)
	{
		if (ft_strncmp(list->cmd[arg], envp->name[x],
				ft_strlen(envp->name[x])) == 0)
		{
			list->envvarpos = x;
			return (1);
		}
		x++;
	}
	return (0);
}

int	unsetit(struct s_envp *envp, t_cmd *list, int arg)
{
	int		x;
	char	**new;

	x = 0;
	new = (char **)malloc(sizeof(char *) * envp->envpitems - 1);
	envp->envpitems--;
	while (x < envp->envpitems)
	{
		if (x < list->envvarpos)
			new[x] = envp->environment[x];
		if (x >= list->envvarpos)
			new[x] = envp->environment[x + 1];
		x++;
	}
	envp->environment = new;
	// free2d(new);
	ft_split_env(envp, envp->environment);
	return (SUCCESSFUL);
}

int	ft_unset(struct s_envp *envp, t_cmd *list, int arg)
{
	int	x;
	int	i;
	int	next;

	x = 0;
	list->envvarpos = -1;
	i = 0;
	x = 0;
	next = 0;
	if (ft_search_for_variable_in_env(envp, list, arg) == 1)
	{
		unsetit(envp, list, arg);
	}
	return (SUCCESSFUL);
}

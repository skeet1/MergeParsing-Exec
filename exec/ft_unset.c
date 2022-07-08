/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:15:57 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/08 21:09:42 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

int	ft_equal_sign(struct s_envp *envp, t_cmd *list, int arg)
{
	int	i;

	i = 0;
	while (list->cmd[arg][i])
	{
		if (list->cmd[arg][i] == '=')
		{
			printf("Minishell: unset: `%s': not a valid identifier\n",
				list->cmd[arg]);
			return (0);
		}
		i++;
	}
	return (1);
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
		// list->envsplited = ft_split(envp->environment[x], '=');
		if (ft_strncmp(list->cmd[arg],envp->name[x],  ft_strlen(envp->name[x])) == 0)
		{
			list->envvarpos = x;
			return (1);
		}
		x++;
	}
	return (0);
}
int	ft_unset(struct s_envp *envp, t_cmd  *list, int arg)
{
	int x = 0;
	char *to_be_unset;
	char **new;
	list->envvarpos = -1;
	int i = 0;

	x = 0;
	int next = 0;
			printf("args %s\n",list->cmd[arg] );

	if (ft_search_for_variable_in_env(envp, list, arg) == 1)
	{
			new = malloc(sizeof(char **) * envp->envpitems - 1);
	int lenght = ft_strlen(list->cmd[arg]);
		printf("found  in pos %d \n", list->envvarpos);
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
		ft_split_env(envp, envp->environment);
		return (0);
	}
	

	return (0);
}
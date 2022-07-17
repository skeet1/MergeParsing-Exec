/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:26:32 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/17 11:16:59 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	*ft_free_2d(char **array)
{
	int	i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (NULL);
}

char	**joinnameand_value(t_lis *envp)
{
	int		i;
	char	**joined;
	char	*tmp1;
	t_env	*en;
	int		envpitems;

	i = 0;
	envpitems = ft_lstsize(envp);
	joined = malloc(sizeof(char *) * (envpitems + 1));
	if (!joined)
		return (NULL);
	while (envp != NULL)
	{
		en = envp->content;
		tmp1 = ft_strjoin(en->name, "=\"");
		if (en->value == NULL)
			en->value = NULL;
		joined[i] = ft_strjoin(tmp1, en->value);
		free(tmp1);
		i++;
		envp = envp->next;
	}
	return (joined);
}

int	ft_export_printer(char **joined)
{
	int	x;

	x = 0;
	while (joined[x])
	{
		printf("declare -x %s\"\n", joined[x]);
		x++;
	}
	return (SUCCESSFUL);
}

int	ft_export_1(t_lis *envp, char **joined)
{
	int		i;
	int		j;
	char	*tmp;
	int		envpitems;

	envp = envp->next;
	joined = joinnameand_value(envp);
	i = 0;
	envpitems = ft_lstsize(envp);
	while (i < envpitems)
	{
		j = i + 1;
		while (j < envpitems)
		{
			if (ft_strcmp(joined[i], joined[j]) > 0)
			{
				tmp = joined[i];
				joined[i] = joined[j];
				joined[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (ft_export_printer(joined));
}

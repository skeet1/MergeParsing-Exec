/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:26:32 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/14 10:30:59 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

char	**join_name_and_value(struct s_envp *envp)
{
	int		i;
	char	**joined;
	char	*tmp1;

	i = 0;
	joined = (char **)malloc(sizeof(char *) * envp->envpitems + 1);
	i = 0;
	while (i < envp->envpitems)
	{
		tmp1 = ft_strjoin(envp->name[i], "=\"");
		if (envp->value[i] == NULL)
			envp->value[i] = "";
		joined[i] = ft_strjoin(tmp1, envp->value[i]);
		free(tmp1);
		i++;
	}
	return (joined);
}

char	**ft_sort_env(struct s_envp *envp)
{
	int		i;
	int		j;
	char	*tmp;
	char	**joined;

	joined = join_name_and_value(envp);
	i = 0;
	while (i < envp->envpitems)
	{
		j = i + 1;
		while (j < envp->envpitems)
		{
			if (ft_strcmp(envp->name[i], envp->name[j]) > 0)
			{
				tmp = joined[i];
				joined[i] = joined[j];
				joined[j] = tmp;
				
			}
			j++;
		}
		i++;
	}
	return (joined);
}

int	ft_export_1(struct s_envp *envp)
{
	int		i;
	int		x;
	char	**joined;

	x = 0;
	i = 0;
	if(envp->environment > 0)
	{
		
	
	ft_copy_1st_env(envp, envp->environment);
	joined = ft_sort_env(envp);
	i = 0;
	while (i < envp->envpitems)
	{
		printf("declare -x %s\"\n", joined[i]);
		i++;
	}
	// free2d(joined);
	return (SUCCESSFUL);
	}
		return (UNSUCCESSFUL);

}

int	check_name_is_valid(char **split, int i, t_cmd *cmd)
{
	if (ft_is_alpha_mod(split[0][0]) == 0)
	{
		printf("Minishell: export: `%s': not a valid identifier\n",
			cmd->cmd[i]);
		return (1);
	}
	return (0);
}

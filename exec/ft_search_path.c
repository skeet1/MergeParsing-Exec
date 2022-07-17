/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 09:58:12 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/17 11:09:23 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	ft_search_for_path(t_cmd *list, t_lis *envp)
{
	int		x;
	t_env	*envval;

	envp = envp->next;
	x = 0;
	while (envp)
	{
		envval = envp->content;
		if (ft_strncmp(envval->name, "PATH", 5) == 0)
		{
			list->new = ft_split(envval->value, ':');
			return (SUCCESSFUL);
		}
		envp = envp->next;
	}
	return (0);
}

void	ftcheck_nopath(t_cmd *list, t_lis *envp)
{
	list->new = NULL;
	ft_search_for_path(list, envp);
	if (list->new == NULL)
	{
		ft_putstr_fd("Minishell : ", 2);
		ft_putstr_fd(list->cmd[0], 2);
		ft_putstr_fd("  No such file or directory\n", 2);
		g_exit_status = 127;
		exit(127);
	}
}

void	looping_through_split_path(t_cmd *list, char *bin, char *last,
		t_lis *envp)
{
	int		i;
	char	**en;

	en = convertlisttoarray(envp);
	i = 0;
	while (list->new[i])
	{
		last = ft_strjoin(bin, list->cmd[0]);
		if (access(last, F_OK) == 0)
		{
			execve(last, list->cmd, en);
			exit(127);
		}
		else
		{
			bin = ft_strjoin(list->new[i], "/");
			last = ft_strjoin(bin, list->cmd[0]);
			i++;
		}
	}
}

int	ft_search(char *s, char *c, int lenght)
{
	int	i;

	i = 1;
	while (i < lenght)
	{
		if (s[i] == c[i])
		{
			i++;
			if (i == lenght)
			{
				return (1);
			}
		}
		else
			return (0);
	}
	return (0);
}

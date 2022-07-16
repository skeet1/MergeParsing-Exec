/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 09:58:12 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/16 16:29:29 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	ft_search_for_path(t_cmd *list, struct s_environ *environ)
{
	int		x;

	x = 0;
	while (environ)
	{
		if (ft_strncmp(environ->name, "PATH", 5) == 0)
		{
			list->new = ft_split(environ->value, ':');
			return (SUCCESSFUL);
		}
		environ = environ->next;
	}
	return (0);
}

void	ftcheck_nopath(t_cmd *list, struct s_environ *environ)
{
	list->new = NULL;
	ft_search_for_path(list, environ);
	if (list->new == NULL)
	{
		ft_putstr_fd("Minishell : ", 2);
		ft_putstr_fd(list->cmd[0], 2);
		ft_putstr_fd("No such file or directory\n", 2);
		g_exit_status = 127;
		exit(127);
	}
}

void	looping_through_split_path(t_cmd *list, char *bin, char *last,
		struct s_environ *environ)
{
	int		i;
	char	**en;

	en = convertlisttoarray(list, environ);
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

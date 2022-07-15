/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 09:58:12 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/15 13:04:16 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	ft_search_for_path(t_cmd *list, struct s_environ *environ)
{
	int		x;
	char	**new;
	int		i;

	x = 0;
	while (environ)
	{
		if (ft_strncmp(environ->name, "PATH", 5) == 0)
		{
			list->new = ft_split(environ->value, ':');
			printf("%s\n\n", environ->value);
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
		printf("MINISHELL : %s No such file or directory\n",
				list->cmd[0]);
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
			list->args_execve = create_argv_for_execve(list);
			execve(last, list->args_execve, en);
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

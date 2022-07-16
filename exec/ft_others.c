/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_others.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:24:12 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/16 09:08:17 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_list_items(struct s_environ *environ)
{
	int	items;

	items = 0;
	while (environ)
	{
		items++;
		environ = environ->next;
	}
	return (items);
}

char	**convertlisttoarray(t_cmd *cmd, struct s_environ *environ)
{
	int		i;
	char	**envir;
	int		len;

	i = 0;
	len = 0;
	len = ft_list_items(environ);
	envir = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		envir[i] = environ->env;
		i++;
		environ = environ->next;
	}
	envir[i] = NULL;
	return (envir);
}

int	ft_check_programs(t_cmd *cmd, struct s_environ *environ)
{
	char	**en;

	en = convertlisttoarray(cmd, environ);
	if (cmd->cmd[0][0] == '.' && cmd->cmd[0][1] == '/')
	{
		execve(cmd->cmd[0], cmd->cmd, en);
		ft_putstr_fd("Minishell : ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd("No such file or directory\n", 2);
		exit(127);
	}
	if (cmd->cmd[0][0] == '/')
	{
		execve(cmd->cmd[0], cmd->cmd, en);
		ft_putstr_fd("Minishell : ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd("No such file or directory\n", 2);
		exit(127);
	}
	return (0);
}

int	ft_bin_usr_sbin(t_cmd *cmd, struct s_environ *environ)
{
	char	*bin;
	char	*last;

	last = NULL;
	ft_check_programs(cmd, environ);
	ftcheck_nopath(cmd, environ);
	bin = ft_strjoin(cmd->new[0], "/");
	looping_through_split_path(cmd, bin, last, environ);
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(cmd->cmd[0], 2);
	write(2, " command not found \n", 21);
	g_exit_status = 127;
	exit(127);
}

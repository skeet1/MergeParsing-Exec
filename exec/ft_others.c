/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_others.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:24:12 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/17 11:19:02 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	ft_list_items(t_lis *envp)
{
	int	items;

	items = 0;
	while (envp)
	{
		items++;
		envp = envp->next;
	}
	return (items);
}

char	**joinnameandvaluetosort(t_lis *envp)
{
	int		i;
	char	**joined;
	char	*tmp1;
	t_env	*env;
	int		len;

	len = ft_list_items(envp);
	i = 0;
	joined = malloc(sizeof(char **) * (len + 1));
	if (!joined)
		return (NULL);
	i = 0;
	while (envp)
	{
		env = envp->content;
		tmp1 = ft_strjoin(env->name, "=");
		if (env->value == NULL)
			env->value = NULL;
		joined[i] = ft_strjoin(tmp1, env->value);
		i++;
		envp = envp->next;
	}
	joined[i] = NULL;
	return (joined);
}

char	**convertlisttoarray(t_lis *envp)
{
	char	**new;

	new = joinnameandvaluetosort(envp);
	return (new);
}

int	ft_check_programs(t_cmd *cmd, t_lis *envp)
{
	char	**en;

	en = convertlisttoarray(envp);
	if (cmd->cmd[0][0] == '.' && cmd->cmd[0][1] == '/')
	{
		execve(cmd->cmd[0], cmd->cmd, en);
		ft_putstr_fd("Minishell : ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(" No such file or directory\n", 2);
		exit(127);
	}
	if (cmd->cmd[0][0] == '/')
	{
		execve(cmd->cmd[0], cmd->cmd, en);
		ft_putstr_fd("Minishell : ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(" No such file or directory\n", 2);
		exit(127);
	}
	return (0);
}

int	ft_bin_usr_sbin(t_cmd *cmd, t_lis *envp)
{
	char	*bin;
	char	*last;

	last = NULL;
	ft_check_programs(cmd, envp);
	ftcheck_nopath(cmd, envp);
	bin = ft_strjoin(cmd->new[0], "/");
	looping_through_split_path(cmd, bin, last, envp);
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(cmd->cmd[0], 2);
	write(2, " command not found \n", 21);
	g_exit_status = 127;
	exit(127);
}

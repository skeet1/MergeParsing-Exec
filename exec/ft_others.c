/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_others.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:24:12 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/13 08:56:57 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**create_argv_for_execve(t_cmd *cmd)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	len = cmd->count_args;
	if (len == 0)
	{
		cmd->args_execve = (char **)malloc(sizeof(char *) * (2));
		cmd->args_execve[0] = cmd->cmd[0];
		cmd->args_execve[1] = NULL;
		return (cmd->args_execve);
	}
	cmd->args_execve = (char **)malloc(sizeof(char *) * (len + 2));
	while (i < len)
	{
		cmd->args_execve[0] = cmd->cmd[0];
		cmd->args_execve[i + 1] = cmd->cmd[i + 1];
		i++;
	}
	cmd->args_execve[i + 1] = NULL;
	return (cmd->args_execve);
}

int	ft_check_programs(t_cmd *cmd, struct s_envp *envp)
{
	char	**argv;

	if (cmd->cmd[0][0] == '.' && cmd->cmd[0][1] == '/')
	{
		argv = create_argv_for_execve(cmd);
		execve(cmd->cmd[0], argv, envp->environment);
		printf("Minishell : %s : No such file or directory\n",
			cmd->cmd[0]);
		exit(127);
	}
	if (cmd->cmd[0][0] == '/')
	{
		argv = create_argv_for_execve(cmd);
		execve(cmd->cmd[0], argv, envp->environment);
		printf("Minishell : %s : No such  file or directory\n",
			cmd->cmd[0]);
		exit(127);
	}
	return (0);
}

int	ft_bin_usr_sbin(t_cmd *cmd, struct s_envp *envp)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 10:41:00 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/12 19:24:12 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	free2d(char **s)
{
	int	i;

	i = 0;
	if (s[i])
		return (0);
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (0);
}

int	check_exit_no_args(t_cmd *cmd, struct s_envp *envp)
{
	if (cmd->cmd[1] == NULL)
	{
		printf("exit\n");
		rl_clear_history();
	// free2d(envp->copy);
		free2d(envp->name);
		free2d(envp->value);
				free2d(envp->environment);
		exit(g_exit_status);
	}
	return (0);
}

int	check_exit_with_args(t_cmd *cmd, struct s_envp *envp)
{
	int	i;
	int	exit_value;

	i = 0;
	if (cmd->cmd[2] == NULL)
	{
		i = 0;
		while (cmd->cmd[1])
		{
			while (cmd->cmd[1][i])
			{
				if (!(ft_isdigit(cmd->cmd[1][i])))
				{
					printf("exit\n");
					printf("Minishell: exit: %s: numeric argument required\n",
						cmd->cmd[1]);
					free2d(envp->name);
					free2d(envp->value);
					exit(255);
				}
				i++;
			}
			exit_value = ft_atoi(cmd->cmd[1]);
			free2d(envp->name);
			free2d(envp->value);
			exit(exit_value);
		}
	}
	return (0);
}

int	ftexit(t_cmd *cmd, struct s_envp *envp)
{
	check_exit_no_args(cmd, envp);
	check_exit_with_args(cmd, envp);
	printf("exit\n Minishell : exit : too many arguments\n");
	free2d(envp->name);
	free2d(envp->value);
	g_exit_status = 2;
	exit(2);
}

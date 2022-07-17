/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 08:34:24 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/16 21:45:33 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	check_exit_no_args(t_cmd *cmd, t_lis *envp)
{
	if (cmd->cmd[1] == NULL)
	{
		printf("exit\n");
		rl_clear_history();
		// free_environ(&envp);
		exit(g_exit_status);
	}
	return (0);
}

void	exitwithnonnumeric(t_cmd *cmd, t_lis *envp, int i)

{
	if (!(ft_isdigit(cmd->cmd[1][i])))
	{
		printf("exit\n");
		printf("Minishell: exit: %s: numeric argument required\n",
			cmd->cmd[1]);
		// free_environ(&envp);
		exit(255);
	}
}

int	check_exit_with_args(t_cmd *cmd, t_lis *envp)
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
				exitwithnonnumeric(cmd, envp, i);
				i++;
			}
			exit_value = ft_atoi(cmd->cmd[1]);
			// free_environ(&envp);
			exit(exit_value);
		}
	}
	return (0);
}

int	ftexit(t_cmd *cmd, t_lis *envp)
{
	int	i;

	i = 0;
	check_exit_no_args(cmd, envp);
	check_exit_with_args(cmd, envp);
	if (cmd->cmd[2] != NULL)
	{
		while (cmd->cmd[1][i])
		{
			exitwithnonnumeric(cmd, envp, i);
			i++;
		}
	}
	printf("exit\n Minishell : exit : too many arguments\n");
	return (0);
}

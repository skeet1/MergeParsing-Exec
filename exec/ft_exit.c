/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 10:41:00 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/15 09:13:37 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	free2d(char **s)
{
	int	i;

	i = 0;
	// if (s[i])
	// 	return (0);
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (0);
}
int	ft_cleaner(t_cmd *cmd, struct s_environ *envp)
{
	// int	i;

	// i = 0;
	// rl_clear_history();
	// while (i < envp->envpitems)
	// {
	// 	free(envp->name[i]);
	// 	free(envp->value[i]);
	// 	i++;
	// }
	// if (envp->ismalloced == 1)
	// free2d(envp->environment);
	// 	if (envp->malloced == 1)
	// free2d(envp->namevalue);

	// free(envp->name);
	// free(envp->value);

	return (0);
}
int	check_exit_no_args(t_cmd *cmd, struct s_environ *envp)
{
	if (cmd->cmd[1] == NULL)
	{
		printf("exit\n");
		rl_clear_history();
		ft_cleaner(cmd, envp);
		exit(g_exit_status);
	}
	return (0);
}

void	exitwithnonnumeric(t_cmd *cmd, struct s_environ *envp, int i)

{
	if (!(ft_isdigit(cmd->cmd[1][i])))
	{
		printf("exit\n");
		printf("Minishell: exit: %s: numeric argument required\n",
				cmd->cmd[1]);
		ft_cleaner(cmd, envp);

		exit(255);
	}
}

int	check_exit_with_args(t_cmd *cmd, struct s_environ *envp)
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
			ft_cleaner(cmd, envp);
			exit(exit_value);
		}
	}
	return (0);
}

int	ftexit(t_cmd *cmd, struct s_environ *envp)
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

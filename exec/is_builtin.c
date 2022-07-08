/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 10:36:00 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/08 19:46:17 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parse.h"

int	ft_is_alpha_mod(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == 95)
		return (1);
	return (0);
}

int	is_builtin( t_cmd *list, int i)
{
	if (list->cmd[0] == NULL)
		return (0);
	if (ft_strncmp(list->cmd[0], "cd", 3) == 0)
		return (0);
	else if (ft_strncmp(list->cmd[0], "pwd", 4) == 0)
		return (0);
	else if (ft_strncmp(list->cmd[0], "echo", 5) == 0)
		return (0);
	else if (ft_strncmp(list->cmd[0], "env", 4) == 0)
		return (0);
	else if (ft_strncmp(list->cmd[0], "exit", 5) == 0)
		return (0);
	else if (ft_strncmp(list->cmd[0], "unset", 6) == 0)
		return (0);
	else if (ft_strncmp(list->cmd[0], "export", 7) == 0)
		return (0);
	return (3);
}

int	ft_is_built_in(t_cmdl *list, struct s_envp *envp,  t_cmd *cmds)
{
	int	i;

	i = 0;
	if (builtcheck(list, envp, cmds) == 1)
		return (1);
	//  if (builtcheck_1(cmds, envp) == 1)
	// 	return (1);
	// else if (ft_strncmp(list[0].cmd, "env", 4) == 0)
	// {
	// 	g_exit_status = ft_env(envp, list);
	// 	return (1);
	// }
	// else if (ft_strncmp(list[0].cmd, "pwd", 4) == 0)
	// {
	// 	g_exit_status = ft_pwd(list->fd_out);
	// 	return (1);
	// }
	// else if (ft_strncmp(list[0].cmd, "exit", 5) == 0)
	// {
	// 	ftexit(list, envp);
	// }
	return (0);
}

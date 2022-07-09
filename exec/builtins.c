/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:06:50 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/09 10:21:30 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "../parsing/parse.h"

int	ft_echo_c(t_cmd *cmds, int fd)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	while (cmds->cmd[i])
	{
		// if (ft_strncmp(list[list->cmd_iteration].args[i], "$?", 2) == 0)
		// {
		// 	printf(" %d \n", g_exit_status);
		// 	return (0);
		// }
		len = ft_strlen(cmds->cmd[i]);
		write(fd, " ", 1);
		write(fd, cmds->cmd[i], len);
		i++;
	}
	write(fd, "\n", 1);
	return (0);
}

int	ft_echo( t_cmd *cmds, int fd)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	if (cmds->cmd[1] == NULL)
	{
		write(fd, "\n", 1);
		return (0);
	}
	else
	{
		ft_echo_c(cmds, fd);
	}
	return (0);
}

int	ft_pwd(int fd_out)
{
	char	pw[PATH_MAX];
	char	*pwd;
	int		len;

	len = 0;
	pwd = getcwd(pw, PATH_MAX);
	len = ft_strlen(pwd);
	write(fd_out, pwd, len);
	write(fd_out, "\n", 1);
	return (0);
}

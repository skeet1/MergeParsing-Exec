/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:06:50 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/14 08:26:48 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "../parsing/parse.h"

int	ft_echo_n(t_cmd *cmds, int fd)
{
	int	i;

	i = 1;
	if (cmds->cmd[1] != NULL && cmds->cmd[1][0] == '-'
		&& cmds->cmd[1][1] == 'n')
	{
		while (cmds->cmd[1][i] != '\0')
		{
			if (cmds->cmd[1][i] != 'n')
				return (UNSUCCESSFUL);
			i++;
		}
	}
	else
		return (UNSUCCESSFUL);
	return (SUCCESSFUL);
}

int	ft_echo_c(t_cmd *cmds, int fd)
{
	int	i;
	int	len;
	int	check;

	check = UNSUCCESSFUL;
	i = 1;
	len = 0;
	while (cmds->cmd[i])
	{
		if (ft_echo_n(cmds, fd) == SUCCESSFUL && i == 1)
		{
			check = SUCCESSFUL;
			i++;
		}
		len = ft_strlen(cmds->cmd[i]);
		write(fd, cmds->cmd[i], len);
		i++;
		if (cmds->cmd[i])
			write(fd, " ", 1);
		else if (cmds->cmd[i] == NULL && check == UNSUCCESSFUL)
			write(fd, "\n", 1);
	}
	if (check == UNSUCCESSFUL)
		write(fd, "\n", 1);
	return (SUCCESSFUL);
}

int	ft_echo(t_cmd *cmds, int fd)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	if (cmds->cmd[1] == NULL)
	{
		write(fd, "\n", 1);
		return (SUCCESSFUL);
	}
	else if (cmds->cmd[1] != NULL)
		ft_echo_c(cmds, fd);
	return (SUCCESSFUL);
}

int	ft_pwd(int fd_out)
{
	char	*pwd;
	int		len;

	len = 0;
	pwd = getcwd(NULL, PATH_MAX);
	if (pwd == NULL)
	{
		perror("Minishell : ");
		return (UNSUCCESSFUL);
	}
	len = ft_strlen(pwd);
	write(fd_out, pwd, len);
	write(fd_out, "\n", 1);
	return (SUCCESSFUL);
}

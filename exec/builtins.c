/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:06:50 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/17 12:28:09 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "../parsing/parse.h"

int	ft_echo_n(char *args)
{
	int	i;

	i = 1;
	if (args != NULL && args[0] == '-' && args[1] == 'n')
	{
		while (args[i] != '\0')
		{
			if (args[i] != 'n')
				return (UNSUCCESSFUL);
			i++;
		}
	}
	else
		return (UNSUCCESSFUL);
	return (SUCCESSFUL);
}

int	ft_echo_c(t_cmd *cmds, int fd, int notfound)
{
	int	i;
	int	check;

	check = UNSUCCESSFUL;
	i = 1;
	while (cmds->cmd[i])
	{
		if (ft_echo_n(cmds->cmd[i]) == SUCCESSFUL)
			notfound = 0;
		if (ft_echo_n(cmds->cmd[i]) == UNSUCCESSFUL)
		{
			while (cmds->cmd[i])
			{
				write(fd, cmds->cmd[i], ft_strlen(cmds->cmd[i]));
				if (cmds->cmd[i + 1])
					write(fd, " ", 1);
				i++;
			}
			if (notfound == 1)
				write(fd, "\n", 1);
			return (SUCCESSFUL);
		}
		i++;
	}
	return (SUCCESSFUL);
}

int	ft_echo(t_cmd *cmds, int fd)
{
	int	len;
	int	i;
	int	notfound;

	notfound = 1;
	i = 0;
	len = 0;
	if (cmds->cmd[1] == NULL)
	{
		write(fd, "\n", 1);
		return (SUCCESSFUL);
	}
	else if (cmds->cmd[1] != NULL)
		ft_echo_c(cmds, fd, notfound);
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

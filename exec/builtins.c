/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:06:50 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/08 12:42:09 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "../parsing/parse.h"

int	ft_echo_c(t_cmdl *list, int fd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < list->count_args)
	{
		if (ft_strncmp(list[list->cmd_iteration].args[i], "$?", 2) == 0)
		{
			printf(" %d \n", g_exit_status);
			return (0);
		}
		len = ft_strlen(list->args[i]);
		write(fd, " ", 1);
		write(fd, list->args[i], len);
		i++;
	}
	write(fd, "\n", 1);
	return (0);
}

int	ft_echo(t_cmdl *list, int fd)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	if (list[0].args[0] == NULL)
	{
		write(fd, "\n", 1);
		return (0);
	}
	else
	{
		ft_echo_c(list, fd);
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

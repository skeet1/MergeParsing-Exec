/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:38:46 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/16 16:47:24 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "parse.h"

void	red(void)
{
	ft_putstr_fd("\033[1;31m", 0);
}

void	reset(void)
{
	ft_putstr_fd("\033[0m", 0);
}

int	consec_redout(char *s)
{
	int	i;
	int	sec;

	i = 0;
	sec = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i] == '>')
			sec++;
		else
			sec = 0;
		if (sec > 2)
			return (ft_putstr_fd(SNT_ERR, 2), ft_putendl_fd(">'", 2), 1);
		i++;
	}
	return (0);
}

int	consec_redin(char *s)
{
	int	i;
	int	sec;

	i = 0;
	sec = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i] == '<')
			sec++;
		else
			sec = 0;
		if (sec > 2)
			return (ft_putstr_fd(SNT_ERR, 2), ft_putendl_fd("<'", 2), 1);
		i++;
	}
	return (0);
}

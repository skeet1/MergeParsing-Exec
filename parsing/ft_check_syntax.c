/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 09:34:37 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/15 11:35:17 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "parse.h"

int	consec_red1(char *s)
{
	int		i;
	int		j;
	int		quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	while (s[i])
	{
		incr_quotes(s[i], &quotes[0], &quotes[1]);
		if (quotes[0] % 2 || quotes[1] % 2)
		{
			i++;
			continue;
		}
		if (s[i] == '>')
		{
			j = i - 1;
			while (j >= 0 && ft_isspace(s[j]))
				j--;
			if (s[j] == '<')
				return (1);
			j = i + 1;
			while (j < ft_strlen(s) && ft_isspace(s[j]))
				j++;
			if (s[j] == '<')
				return (1);
		}
		i++;
	}
	return (0);
}

int	consec_red2(char *s)
{
	int		i;
	int		j;
	int		quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	while (s[i])
	{
		incr_quotes(s[i], &quotes[0], &quotes[1]);
		if (quotes[0] % 2 || quotes[1] % 2)
		{
			i++;
			continue;
		}
		if (s[i] == '<')
		{
			j = i - 1;
			while (j >= 0 && ft_isspace(s[j]))
				j--;
			if (s[j] == '>')
				return (1);
			j = i + 1;
			while (j < ft_strlen(s) && ft_isspace(s[j]))
				j++;
			if (s[j] == '>')
				return (1);
		}
		i++;
	}
	return (0);
}

int	consec_redout(char *s)
{
	int		i;
	int		sec;

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
			return (ft_putstr_fd(SNT_ERR, 2), ft_putendl_fd(">", 2), 1);
		i++;
	}
	return (0);
}

int	consec_redin(char *s)
{
	int		i;
	int		sec;

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
			return (ft_putstr_fd(SNT_ERR, 2), ft_putendl_fd("<", 2), 1);
		i++;
	}
	return (0);
}

int	check_parent(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ')' || s[i] == '(')
		{
			return (ft_putstr_fd(SNT_ERR, 2), ft_putchar_fd(s[i], 2), ft_putendl_fd("", 2), 1);
		}
		i++;
	}
	return (0);
}

int	check_red(char *s)
{
	int		len;
	int		i;
	int		j;
	int		quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	len = ft_strlen(s);
	i = 0;
	if (s[len - 1] == '>' || s[len - 1] == '<' || consec_red1(s) || consec_red2(s))
		return(ft_putstr_fd(SNT_ERR, 1), ft_putendl_fd("newline'", 1), 1);
	if (consec_redin(s) || consec_redout(s))
		return (1);
	return (0);
}

void red()
{
  ft_putstr_fd("\033[1;31m", 0);
}

void reset()
{
  ft_putstr_fd("\033[0m", 0);
}

int	ft_check_syntax(t_data *data, char *s)
{
	data->error = 0;
	red();
	if (check_pipes(s) || check_quotes(s) || check_red(s) || check_parent(s))
	{
		data->error = 1;
		g_exit_status = 258;
		return (reset(), 1);
	}
	return (reset(), 0);
}
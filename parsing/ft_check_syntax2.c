/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:38:46 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/15 12:15:49 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "parse.h"

int	consec_red1_help(char *s, int *i, int *j, int len)
{
	*j = *i - 1;
	while (*j >= 0 && ft_isspace(s[*j]))
		(*j)--;
	if (s[*j] == '<')
		return (1);
	*j = *i + 1;
	while (*j < len && ft_isspace(s[*j]))
		(*j)++;
	if (s[*j] == '<')
		return (1);
	return (0);
}

int	consec_red2_help(char *s, int *i, int *j, int len)
{
	*j = *i - 1;
	while (*j >= 0 && ft_isspace(s[*j]))
		(*j)--;
	if (s[*j] == '>')
		return (1);
	*j = *i + 1;
	while (*j < len && ft_isspace(s[*j]))
		(*j)++;
	if (s[*j] == '>')
		return (1);
	return (0);
}

int	consec_red1(char *s)
{
	int	i;
	int	j;
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = -1;
	j = 0;
	while (s[++i])
	{
		incr_quotes(s[i], &quotes[0], &quotes[1]);
		if (quotes[0] % 2 || quotes[1] % 2)
		{
			i++;
			continue ;
		}
		if (s[i] == '>')
			if (consec_red1_help(s, &i, &j, ft_strlen(s)))
				return (1);
	}
	return (0);
}

int	consec_red2(char *s)
{
	int	i;
	int	j;
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = -1;
	while (s[++i])
	{
		incr_quotes(s[i], &quotes[0], &quotes[1]);
		if (quotes[0] % 2 || quotes[1] % 2)
		{
			i++;
			continue ;
		}
		if (s[i] == '<')
			if (consec_red2_help(s, &i, &j, ft_strlen(s)))
				return (1);
	}
	return (0);
}

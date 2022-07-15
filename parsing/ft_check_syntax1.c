/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:32:16 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/15 11:33:01 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "parse.h"

int	ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
int	is_special(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	check_quotes(char *s)
{
	int	i;
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && quotes[1] % 2 == 0)
			quotes[0]++;
		else if (s[i] == '"' && quotes[0] % 2 == 0)
			quotes[1]++;
		i++;
	}
	if (quotes[0] % 2 || quotes[1] % 2)
		return (ft_putendl_fd("Quotes Syntax Error! *RELANCH MINISHELL*", 2),
			1);
	return (0);
}

int	check_pipes(char *s)
{
	int	i;
	int	j;
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	if (s[0] == '|' || s[ft_strlen(s) - 1] == '|')
		return (ft_putstr_fd(SNT_ERR, 2), ft_putendl_fd("|'", 2), 1);
	while (s[i])
	{
		if (s[i] == '\'')
			quotes[0]++;
		else if (s[i] == '"')
			quotes[1]++;
		if (quotes[0] % 2 || quotes[1] % 2)
		{
			i++;
			continue ;
		}
		if (s[i] == '|')
		{
			j = i - 1;
			while (j >= 0 && ft_isspace(s[j]))
				j--;
			if (s[j] == '|')
				return (ft_putstr_fd(SNT_ERR, 2), ft_putendl_fd("|'", 2), 1);
			j = i + 1;
			while (j < ft_strlen(s) && ft_isspace(s[j]))
				j++;
			if (s[j] == '|')
				return (ft_putstr_fd(SNT_ERR, 2), ft_putendl_fd("|'", 2), 1);
		}
		i++;
	}
	return (0);
}

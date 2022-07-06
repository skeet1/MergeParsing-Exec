/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 09:34:37 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/06 11:53:06 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../libft/libft.h"
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
	int		i;
	int		quotes[2];

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
		return (ft_putendl_fd("Quotes Syntax Error! *RELANCH MINISHELL*", 1), 1);
	return (0);
}

int	check_pipes(char *s)
{
	int		i;
	int		j;
	int		quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	if (s[0] == '|' || s[ft_strlen(s) - 1] == '|')
		return (ft_putstr_fd(SNT_ERR, 1), ft_putendl_fd("|'", 1), 1);
	while (s[i])
	{
		if (s[i] == '\'')
			quotes[0]++;
		else if (s[i] == '"')
			quotes[1]++;
		if (quotes[0] % 2 || quotes[1] % 2)
		{
			i++;
			continue;
		}
		if (s[i] == '|')
		{
			j = i - 1;
			while (j >= 0 && ft_isspace(s[j]))
				j--;
			if (s[j] == '|')
				return (ft_putstr_fd(SNT_ERR, 1), ft_putendl_fd("|'", 1), 1);
			j = i + 1;
			while (j < ft_strlen(s) && ft_isspace(s[j]))
				j++;
			if (s[j] == '|')
				return (ft_putstr_fd(SNT_ERR, 1), ft_putendl_fd("|'", 1), 1);
		}
		i++;
	}
	return (0);
}

int	check_red(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (s[len - 1] == '>' || s[len - 1] == '<')
		return(ft_putstr_fd(SNT_ERR, 1), ft_putendl_fd("newline'", 1), 1);
	return (0);
}

void red() {
  ft_putstr_fd("\033[1;31m", 1);
}

void reset() {
  ft_putstr_fd("\033[0m", 1);
}

int	ft_check_syntax(char *s)
{
	red();
	if (check_pipes(s) || check_quotes(s) || check_red(s))
		return (reset(), 1);
	return (reset(), 0);
}
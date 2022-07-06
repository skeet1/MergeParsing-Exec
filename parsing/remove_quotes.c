/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:36:54 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/05 15:09:56 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	len_without_quotes(char *s)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '"')
			len++;
		i++;
	}
	return (len);
}

char	*trim_quotes(char *s)
{
	char	*cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd = malloc(len_without_quotes(s) + 1);
	if (!cmd)
		return (cmd);
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '"')
			cmd[j++] = s[i];
		i++;
	}
	return (cmd);
}

void	remove_quotes(t_token *token)
{
	while (token)
	{
		token->value = trim_quotes(token->value);
		token = token->next;
	}
}
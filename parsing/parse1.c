/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:47:50 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/16 17:05:48 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "parse.h"

void	mark_cmd(t_token *tok)
{
	t_token	*token;
	int		pipe;
	int		i;

	pipe = 1;
	token = tok;
	while (token)
	{
		token->args_num = 0;
		if (pipe && token->type == WORD)
		{
			token->type = CMD;
			i = -1;
			while (token->value[++i])
				token->value[i] = ft_tolower(token->value[i]);
			pipe = 0;
		}
		else if (token->type == WORD)
			token->type = ARG;
		else if (token->type == PIPE)
			pipe = 1;
		token = token->next;
	}
}

char	*rm_first_char(char *str)
{
	char	*s;
	int		len;
	int		i;

	if (str)
	{
		len = ft_strlen(str);
		s = (char *)malloc(len);
		if (!s)
			return (s);
		i = 0;
		if (str[i])
			i++;
		while (str[i])
		{
			s[i - 1] = str[i];
			i++;
		}
		s[i - 1] = '\0';
		return (s);
	}
	return (NULL);
}

char	*before_dol(char *str)
{
	int		i;
	char	*s;

	i = 0;
	while (str[i] && str[i] != '$')
	{
		i++;
	}
	s = malloc(i + 1);
	i = 0;
	while (str[i] && str[i] != '$')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	dolar_exist(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*rest_cmp(char *str, int len)
{
	char	*s;
	int		i;

	s = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (!s)
		return (s);
	i = 0;
	while (str[len + i])
	{
		s[i] = str[len + i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

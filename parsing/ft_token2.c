/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:42:10 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/17 12:04:36 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "parse.h"

void	token_assist(char *s, int *j, int *a, int *b)
{
	incr_quotes(s[*j], a, b);
	while ((s[*j] && !ft_isspace(s[*j]) && !is_special(s[*j])) || (s[*j]
			&& ((*a) % 2 || (*b) % 2)))
	{
		incr_quotes(s[*j], a, b);
		if ((*b) % 2 || (*a) % 2)
			(*j)++;
		if ((*b) % 2 || (*a) % 2)
			continue ;
		(*j)++;
	}
}

void	scape_spaces_or_special(char *s, int *j, int spaces)
{
	if (spaces)
		while (s[*j] && ft_isspace(s[*j]))
			(*j)++;
	else
		while (s[*j] && is_special(s[*j]))
			(*j)++;
}

void	incr_quotes_assist_token(char c, int *j, int *a, int *b)
{
	incr_quotes(c, a, b);
	if (*b % 2 || *a % 2)
		(*j)++;
}

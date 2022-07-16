/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:42:10 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/16 19:10:39 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "parse.h"

void	incr_quotes(char c, int *a, int *b)
{
	if (c == '\'' && (*b) % 2 == 0)
		(*a)++;
	else if (c == '"' && (*a) % 2 == 0)
		(*b)++;
}

t_token	*ft_token_side(t_token *token, char *s)
{
	int	j;
	int	start;
	int	quotes[2];
	int	node;

	j = 0;
	start = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	node = 0;
	while (s[j])
	{
		incr_quotes(s[j], &quotes[0], &quotes[1]);
		if (quotes[1] % 2 || quotes[0] % 2)
		{
			j++;
			continue ;
		}
		if (!ft_isspace(s[j]) && !is_special(s[j]))
		{
			incr_quotes(s[j], &quotes[0], &quotes[1]);
			while ((s[j] && !ft_isspace(s[j]) && !is_special(s[j])) || (s[j]
					&& (quotes[1] % 2 || quotes[0] % 2)))
			{
				incr_quotes(s[j], &quotes[0], &quotes[1]);
				if (quotes[1] % 2 || quotes[0] % 2)
				{
					j++;
					continue ;
				}
				j++;
			}
			ft_add_back(&token, ft_substr(s, start, j - start + !s[j + 1]));
			start = j;
		}
		while (s[j] && ft_isspace(s[j]))
			j++;
		if (is_special(s[j]))
		{
			while (s[j] && is_special(s[j]))
				j++;
			ft_add_back(&token, ft_substr(s, start, j - start));
			start = j;
		}
	}
	add_file_type(token);
	remove_quotes(token);
	return (token);
}

t_token	*ft_token(t_token *token, t_data *data, char *s)
{
	int	i;
	int	start;
	int	side;

	side = 1;
	i = 0;
	start = i;
	ft_num_cmd_side(data, s);
	data->cmd_sides = ft_split(s, '|');
	if (ft_check_syntax(data, data->cmd_line))
		return (0);
	return (ft_token_side(token, data->cmd_line));
}

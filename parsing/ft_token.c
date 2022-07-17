/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:42:10 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/17 12:04:41 by mkarim           ###   ########.fr       */
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

	ft_init_var(&j, &start, &quotes[0], &quotes[1]);
	while (s[j])
	{
		incr_quotes_assist_token(s[j], &j, &quotes[0], &quotes[1]);
		if (quotes[1] % 2 || quotes[0] % 2)
			continue ;
		if (!ft_isspace(s[j]) && !is_special(s[j]))
		{
			token_assist(s, &j, &quotes[0], &quotes[1]);
			ft_add_back(&token, ft_substr(s, start, j - start + !s[j + 1]));
			start = j;
		}
		scape_spaces_or_special(s, &j, 1);
		if (is_special(s[j]))
		{
			scape_spaces_or_special(s, &j, 0);
			ft_add_back(&token, ft_substr(s, start, j - start));
			start = j;
		}
	}
	return (add_file_type(token), remove_quotes(token), token);
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

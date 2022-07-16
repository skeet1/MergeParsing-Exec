/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:42:10 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/16 19:07:44 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "parse.h"

void	ft_num_cmd_side(t_data *data, char *s)
{
	int	i;
	int	side;

	i = 0;
	side = 1;
	while (s[i])
	{
		if (s[i] == '|')
			side++;
		i++;
	}
	data->side = side;
}

int	ft_token_type(char *value)
{
	if (!ft_strcmp(value, "'"))
		return (S_QUOTE);
	else if (!ft_strcmp(value, "\""))
		return (D_QUOTE);
	else if (!ft_strcmp(value, "<"))
		return (RED_IN);
	else if (!ft_strcmp(value, ">"))
		return (RED_OUT);
	else if (!ft_strcmp(value, "<<"))
		return (RED_IN_APP);
	else if (!ft_strcmp(value, ">>"))
		return (RED_OUT_APP);
	else if (!ft_strcmp(value, "|"))
		return (PIPE);
	return (WORD);
}

// void	print_token(t_token *token)
// {
// 	while (token)
// 	{
// 		printf("type is %d value is %s single quotes %d\n", token->type,
// 				token->value, token->sgl_qt);
// 		token = token->next;
// 	}
// }

void	add_file_type(t_token *token)
{
	while (token->next)
	{
		if (token->type >= 2 && token->type <= 5)
		{
			token->next->type = FILEE;
		}
		token = token->next;
	}
}

t_token	*ft_new_node(char *value)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (new);
	new->sgl_qt = 0;
	if (value[0] == '\'')
		new->sgl_qt = 1;
	new->value = value;
	new->type = ft_token_type(value);
	new->next = NULL;
	return (new);
}

void	ft_add_back(t_token **token, char *value)
{
	t_token	*last;
	t_token	*new;

	last = *token;
	new = ft_new_node(ft_strtrim(value, " "));
	if (new == NULL)
		return ;
	if (last == NULL)
	{
		*token = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
}

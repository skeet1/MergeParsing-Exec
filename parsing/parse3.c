/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:47:50 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/17 12:37:44 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "parse.h"

void	npc_assist_1(t_token **tok, t_tocmd *c, int *a, int *b)
{
	t_token	*token;

	token = *tok;
	while (token)
	{
		while (token && token->type != PIPE)
		{
			if (token->type == WORD)
				c->args[(*a)++] = token->value;
			else if (token->type >= 2 && token->type <= 5)
				c->file_type[(*b)] = token->type;
			else if (token->type == FILEE)
				c->file_name[(*b)++] = token->value;
			token = token->next;
		}
		break ;
	}
}

t_cmd	*node_per_cmd(t_token *token)
{
	t_tocmd	c;
	int		i[2];
	int		a_ft[2];
	t_cmd	*cmd;

	cmd = NULL;
	while (token)
	{
		ft_init_var(&a_ft[0], &a_ft[1], &i[0], &i[1]);
		npc_assist(token, &c, &a_ft[0], &a_ft[1]);
		while (token)
		{
			while (token && token->type != PIPE)
			{
				if (token->type == WORD)
					c.args[i[0]++] = token->value;
				else if (token->type >= 2 && token->type <= 5)
					c.file_type[i[1]] = token->type;
				else if (token->type == FILEE)
					c.file_name[i[1]++] = token->value;
				token = token->next;
			}
			break ;
		}
		null_and_back(&cmd, &c, i[0], i[1]);
		if (token)
			token = token->next;
	}
	return (cmd);
}

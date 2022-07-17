/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:47:50 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/17 12:33:42 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "parse.h"


void	add_back_cmd(t_cmd **cmd, char **args, int *file_type, char **file_name)
{
	t_cmd	*last;
	t_cmd	*new;

	new = new_node_cmd(args, file_type, file_name);
	last = *cmd;
	if (new == NULL)
		return ;
	if (last == NULL)
	{
		*cmd = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
}

void	incr_a_ft(int type, int *a, int *ft)
{
	if (type == WORD)
		(*a)++;
	else if (type >= 2 && type <= 5)
		(*ft)++;
}

void	null_and_back(t_cmd **cmd, t_tocmd *c, int a, int b)
{
	c->args[a] = NULL;
	c->file_type[b] = 0;
	c->file_name[b] = NULL;
	add_back_cmd(cmd, (*c).args, (*c).file_type, (*c).file_name);
}

void	ft_init_var(int *a, int *b, int *c, int *d)
{
	(*a) = 0;
	(*b) = 0;
	(*c) = 0;
	(*d) = 0;
}

void	npc_assist(t_token *tok, t_tocmd *c, int *a, int *ft)
{
	while (tok && tok->type != PIPE)
	{
		incr_a_ft(tok->type, a, ft);
		tok = tok->next;
	}
	c->args = ft_calloc(sizeof(char *), *a + 1);
	c->file_name = ft_calloc(sizeof(char *), *ft + 1);
	c->file_type = ft_calloc(sizeof(int), *ft + 1);
}
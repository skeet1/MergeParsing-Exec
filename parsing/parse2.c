/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:47:50 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/17 12:19:37 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "parse.h"

void	exp_change_value(t_lis *envp, t_token *token)
{
	t_lis	*tmp;
	char	**sp;
	int		j;

	tmp = envp;
	while (token)
	{
		if (token->type == WORD && !token->sgl_qt && dolar_exist(token->value))
		{
			exp_exit_status(&token->value);
			sp = ft_split(token->value, '$');
			j = -1;
			while (sp[++j])
			{
				envp = tmp;
				while (envp)
				{
					token->value = ft_ass_exp(&token->value,
							sp[j], envp->content);
					envp = envp->next;
				}
			}
		}
		token = token->next;
	}
}

t_cmd	*new_node_cmd(char **args, int *file_type, char **file_name)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (new);
	new->cmd = args;
	new->f_name = file_name;
	new->f_type = file_type;
	new->next = NULL;
	return (new);
}

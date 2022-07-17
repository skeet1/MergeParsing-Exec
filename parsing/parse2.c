/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:47:50 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/17 12:14:22 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "parse.h"

char	*rest_from_index(char *str, int ind)
{
	char	*s;
	int		i;

	i = 0;
	s = malloc(ft_strlen(str) - ind - 1);
	if (!s)
		return (s);
	while (str[ind + i + 2])
	{
		s[i] = str[ind + i + 2];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*before_index(char *str, int ind)
{
	int		i;
	char	*s;

	i = 0;
	s = malloc(sizeof(char) * (ind + 1));
	if (!s)
		return (s);
	while (i < ind)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

void	exp_exit_status(char **str)
{
	char	*s;
	int		i;

	s = *str;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
			*str = ft_strjoin(ft_strjoin(before_index(s, i),
						ft_itoa(g_exit_status)), rest_from_index(s, i));
		i++;
	}
}

char	*ft_ass_exp(char **tok_val, char *sp, t_env *env)
{
	char	*token_value;

	token_value = *tok_val;
	if (ft_strcmp(sp, env->name) == 0)
	{
		token_value = ft_strjoin(before_dol(token_value),
				env->value);
		return (token_value);
	}
	else
		token_value = before_dol(token_value);
	return (token_value);
}

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

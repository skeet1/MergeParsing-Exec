/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:42:10 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/06 10:44:21 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../libft/libft.h"

void	ft_num_cmd_side(t_data *data, char *s)
{
	int	i;
	int side;

	i = 0;
	side = 1;
	while (s[i])
	{
		if (s[i] == '|' )
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

void	print_token(t_token *token)
{
	while (token)
	{
		printf("type is %d\t\t value is %s\n", token->type, token->value);
		token = token->next;
	}
}

t_files	*ft_new_node_files(int type, char *name)
{
	t_files *new;

	new = (t_files*)malloc(sizeof(t_files));
	if (!new)
		return (new);
	new->name = name;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	ft_add_back_file(t_files **file, int type, char *name)
{
	t_files	*new;
	t_files *last;

	last = *file;
	new = ft_new_node_files(type, name);
	if (new == NULL)
		return ;
	if (last == NULL)
	{
		*file = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
}

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

void	list_files(t_token *token)
{
	t_files	*file;
	t_token *tmp;

	file = NULL;
	tmp = token;
	while (tmp->next)
	{
		if (tmp->type >= 2 && tmp->type <= 5)
		{
			ft_add_back_file(&file, tmp->type, tmp->next->value);
		}
		tmp = tmp->next;
	}
	while (file)
	{
		printf("name of file is : %s -- type is : %d\n", file->name, file->type);
		file = file->next;
	}
}

// dffdjfs

t_token	*ft_new_node(char *value)
{
	t_token *new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (new);
	new->dbl_st = 0;
	if (value[0] == '\'')
		new->dbl_st = 1;
	new->value = value;
	// printf("%d\n", new->dbl_st);
	new->type = ft_token_type(value);
	new->next = NULL;
	return (new);
}

void	ft_add_back(t_token **token, char *value)
{
	t_token *last;
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

void	incr_quotes(char c, int *a, int *b)
{
	if (c == '\'' && (*b) % 2 == 0)
		(*a)++;
	else if (c == '"' && (*a) % 2 == 0)
		(*b)++;
}

void	ft_token_side(t_token *token, t_data *data, char *s)
{
	int		j;
	int		start;
	int		quotes[2];

	j = 0;
	start = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	int node= 0;
	while (s[j])
	{
		incr_quotes(s[j], &quotes[0], &quotes[1]);
		if (quotes[1] % 2 || quotes[0] % 2)
		{
			j++;
			continue;
		}
		if (!ft_isspace(s[j]) && !is_special(s[j]))
		{
			incr_quotes(s[j], &quotes[0], &quotes[1]);
			while ((s[j] && !ft_isspace(s[j]) && !is_special(s[j])) || (s[j] && (quotes[1] % 2 || quotes[0] % 2)))
			{
				if (s[j] == '\'' && quotes[1] % 2 == 0)
					quotes[0]++;
				else if (s[j] == '"' && quotes[0] % 2 == 0)
					quotes[1]++;
				if (quotes[1] % 2 || quotes[0] % 2)
				{
					j++;
					continue;
				}
				j++;
			}
			ft_add_back(&token, ft_substr(s, start, j - start + !s[j  + 1]));
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
	list_files(token);
	pass_to_exec(token);
}

void	ft_token(t_token *token, t_data *data, char *s)
{
	int     i;
	int		start;
	int		side = 1;

	i = 0;
	start = i;
	ft_num_cmd_side(data, s);
	data->cmd_sides = ft_split(s, '|');
	if (ft_check_syntax(data->cmd_line))
		return ;
	ft_token_side(token, data, data->cmd_line);
}

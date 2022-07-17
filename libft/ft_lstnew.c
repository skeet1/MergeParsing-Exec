/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:21:59 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/17 08:20:39 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lis	*ft_lstnew(void *content)
{
	t_lis	*new;

	new = malloc(sizeof(t_lis));
	if (!new)
		return (new);
	new->content = content;
	new->next = NULL;
	return (new);
}

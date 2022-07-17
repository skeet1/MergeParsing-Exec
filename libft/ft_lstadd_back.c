/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:07:06 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/17 08:23:35 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_lis **lst, t_lis *new)
{
	if (lst && *lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}


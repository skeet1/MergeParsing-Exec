/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:23:01 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/06 14:58:11 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "libft.h"

int	ft_strlen(char const *s)
{
	int		i;
	if(s == NULL)
	return 0;
	i = 0;
	while (s[i])
		i++;
	return (i);
}

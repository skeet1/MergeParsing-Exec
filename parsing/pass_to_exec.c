/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:34:10 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/06 10:36:20 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void    pass_to_exec(t_token *token)
{
    printf("HERE from pass to exec\n");
    print_token(token);
}

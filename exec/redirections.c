/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:50:59 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/06 20:48:38 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parse.h"


int	redirections(t_cmdl *list)
{
	int i = 0;
	int input;
	int output;

	while (list[0].type[i] != NULL)
	{

		// input = dup(0);
		// output = dup(1);
		if (ft_strncmp(list->type[i], ">", 2) == 0)
		{
		printf("inside red FILE OUT %s  type is  %s        \n \n", list->file[i], list->type[i]);

			list->fd_out = open(list->file[i], O_RDWR | O_CREAT | O_TRUNC,
					0600);
			if (list->fd_out == -1)
			{
				printf("bash: No such file or directory\n");
				return 3;
			}
		}
		if (ft_strncmp(list[0].type[i] , "<", 2) == 0)
		{	
			list->fd_in = open(list[0].file[i], O_RDONLY, 0);
			if (list->fd_in == -1)
			{
				printf("bash: No such file or directory\n");
			}
		}
		// if (ft_strncmp(list[0].type[i] , RDAPPEND, 10) == 0)
		// {
		// 	list->fd_out = open(list[0].file[i], O_RDWR | O_CREAT | O_APPEND, 0600);	
		// }
		// if (ft_strncmp(list[0].type[i] , HEREDOC, 7) == 0)
		// {
		// 	list->fd_in = open("f1", O_RDWR | O_CREAT | O_TRUNC, 0600);	
		// }
	

		i++;
	}
	printf("i %d \n\n\n", i);
	return (0);
}

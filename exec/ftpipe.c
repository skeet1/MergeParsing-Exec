/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 08:51:00 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/08 21:55:26 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parse.h"
// problem here
//&& redire_2(list) == 0 i must check previous redirection is not rdout
//  &&  ft_strncmp( list[0].type[1], RDOUT, 7) != 0 not workings
//check echo asd > f1 > f3 << f4
//ls > f1 > f2<< FF
int	redire_2(t_cmd *list)
{
	// int	i;
	// int	input;
	// int	output;
	int	ret;

	// i = 0;
	ret = 0;
	// while (i < list->count_redire)
	// {
	// 	if (ft_strncmp(list[0].type[i], "<<", 3) == 0)
	// 	{
	// 		list->fd_in = open("/tmp/tmpherdoc", O_RDWR | O_CREAT | O_TRUNC, 0600);
	// 	}
	// 	if (ft_strncmp(list[list->cmd_iteration].type[i], ">", 2) == 0)
	// 	{
	// 		list->fd_out = open(list[list->cmd_iteration].file[i],
	// 				O_RDWR | O_CREAT | O_TRUNC, 0600);
	// 		if (list->fd_out == -1)
	// 		{
	// 			printf("bash: No such file or directory\n");
	// 		}
	// 		ret = 1;
	// 	}
	// 	if (ft_strncmp(list[list->cmd_iteration].type[i], "<", 2) == 0)
	// 	{
	// 		list->fd_in = open(list[list->cmd_iteration].file[i], O_RDONLY, 0);
	// 		if (list->fd_in == -1)
	// 		{
	// 			printf("bash: No such file or directory\n");
	// 		}
	// 		ret = 1;
	// 	}
	// 	if (ft_strncmp(list[list->cmd_iteration].type[i], ">>", 3) == 0)
	// 	{
	// 		list->fd_out = open(list[list->cmd_iteration].file[i],
	// 							O_RDWR | O_CREAT | O_APPEND,
	// 							0600);
	// 		ret = 1;
	// 	}
	// 	i++;
	// }
	return (ret);
}

void	ft_pipe(t_cmd *list, struct						s_envp * envp)
{
	// int	i;
	// int	id;
	// int	fd_in;

	// i = 0;
	// fd_in = 0;
	// list->fd_in = 0;
	// list->fd_out = 1;
	// list->cmd_iteration = 0;

	// while (list->cmd_iteration < list->cmd_nbr)
	// {
	// 	pipe(list->fd);
	// 	id = fork();
	// 	if (id == 0)
	// 	{
	// 		// printf("here cmd nbr %d  iteration %d  , args %d\n", list->cmd_nbr, list->cmd_iteration,	list->count_args );

	// 		// printf("list->there_is_pipe %d\n", list->there_is_pipe);
	// 			redire_2(list);
	// 		set_rd(list);
	// 		dup2(list->fd_in, 0);
	// 		if((list->cmd_iteration < list->there_is_pipe ))
	// 			// && list[0].type[0] == NULL)
	// 			// || (list->cmd_iteration < list->there_is_pipe
	// 			// 	&& ft_strncmp(list[0].type[0], ">", 2) != 0))
	// 			dup2(list->fd[1], 1);
					
	// 		close(list->fd[0]);
	// 		// ft_is_built_in(list, envp);
	// 		ft_bin_usr_sbin(list, envp);
	// 	}
	// 	else
	// 	{
			
	// 		close(list->fd[1]);
	// 		list->fd_in = list->fd[0];
	// 		wait(&g_exit_status);
	// 		if (WIFEXITED(g_exit_status))
	// 			g_exit_status = WEXITSTATUS(g_exit_status);
	// 		list->cmd_iteration++;
	// 	}
	// }
}

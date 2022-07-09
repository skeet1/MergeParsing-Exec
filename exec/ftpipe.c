/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 08:51:00 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/09 11:32:08 by atabiti          ###   ########.fr       */
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
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (list->f_type[i])
	{
		if (list->f_type[i] == RED_IN_APP)
		{
			list->fd_in = open("/tmp/tmpherdoc", O_RDWR | O_CREAT | O_TRUNC,
					0600);
		}
		if (list->f_type[i] == RED_OUT)
		{
			list->fd_out = open(list->f_name[i],
								O_RDWR | O_CREAT | O_TRUNC,
								0600);
			if (list->fd_out == -1)
			{
				printf("bash: No such file or directory\n");
			}
			ret = 1;
		}
		if (list->f_type[i] == RED_IN)
		{
			list->fd_in = open(list->f_name[i], O_RDONLY, 0);
			if (list->fd_in == -1)
			{
				printf("bash: No such file or directory\n");
			}
			ret = 1;
		}
		if (list->f_type[i] == RED_OUT_APP)
		{
			list->fd_out = open(list->f_name[i],
								O_RDWR | O_CREAT | O_APPEND,
								0600);
			ret = 1;
		}
		printf("i is %d \n", i);
		i++;
	}
	return (ret);
}

void	ft_pipe(t_cmd *list, struct s_envp *envp)
{
	int	i;
	int	id;
	
	int pipes[2];
	i = 0;
	int fd_in = 0;
	list->cmd_iteration = 0;
	list->fd_out = 1;
	while (list)
	{
		pipe(pipes);//
		id = fork();
		if (id == 0)
		{
			redire_2(list);
			set_rd(list);
			// if((list->cmd_iteration <  list->cmdnbr ))
			// && list[0].type[0] == NULL)
			// || (list->cmd_iteration < list->there_is_pipe
			// 	&& ft_strncmp(list[0].type[0], ">", 2) != 0))
			dup2( fd_in, 0);
			if (list->next)
				dup2(pipes[1], list->fd_out);//
			close(pipes[0]);
			ft_is_built_in(envp, list);
			ft_bin_usr_sbin(list, envp);
		}
		else
		{
			wait(&g_exit_status);
			if (WIFEXITED(g_exit_status))
				g_exit_status = WEXITSTATUS(g_exit_status);
			close(pipes[1]);//
			fd_in = pipes[0];//
			list = list->next;
		}
	}
}

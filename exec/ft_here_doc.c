/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 07:14:58 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/12 10:53:43 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "../parsing/parse.h"

//<< EOF without command
void	handler_in_heredoc(int sig)
{
	if (sig == SIGINT)
		exit(EXIT_FAILURE);
}
int	heredoc_exec_part1(t_cmd *list, int i) //sigfault
{
	int id = fork();
	if(id == -1)
	return (0);
	if (id== 0)
	{
		// signal(SIGINT, handler_in_heredoc);
		// signal(SIGQUIT, SIG_IGN);
		int fd;
		char *line = NULL;

		// dup2(fd,0);

		 fd = open("/tmp/tmpherdoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);

		while (1)
		{
			// signal(SIGQUIT, SIG_IGN);
			// signal(SIGQUIT, handler_in_heredoc);

			line = readline(">");
			if (!line)
			exit(EXIT_SUCCESS);
			int len = 0;
			len = ft_strlen(list->f_name[i]) + 1;
			if (ft_strncmp(line, list->f_name[i], len) == 0)
			{
				break ;
			}
			// if (line != NULL)
			// {
				write(fd, line, ft_strlen(line));
				write(fd, "\n", 1);
			// }
			free(line);
		}
		free(line);
		close(fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
				waitpid(id,&g_exit_status, 0);

		// wait(&g_exit_status);
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		return (g_exit_status);
	}
}
int	heredoc_exec(t_cmd *list) //sigfault
{
	// printf(" delimter");
	//<< f1 << f2 > f not working
	int i = 0;
	while (list)
	{
		// printf(" delimter  =	%s \n",list[list->cmd_iteration].delimiter );

		//i must loop here
		while (list->f_type[i])
		{
			if (list->f_type[i] == RED_IN_APP)
			{
				heredoc_exec_part1(list, i);
				// if(!list->f_type[i])
				// 	return (1);
			}
			i++;
		}

		list = list->next;
	}

	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 07:14:58 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/08 22:49:30 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "../parsing/parse.h"

//<< EOF without command
void	handler_in_heredoc(int sig)
{
	if (sig == SIGINT)
		exit(1);
}
int	heredoc_without_cmd(t_cmd *list) //sigfault
{
	// printf(" delimter");

	int i = 0;
	if (list->f_type != NULL)
	{
		if (list->f_type[i] == RED_IN_APP)
		{
			// printf(" delimter  =	%s \n",list[list->cmd_iteration].delimiter );
			if (fork() == 0)
			{
				//i must loop here
				while(list->f_type[i])
				{

				// signal(SIGINT, handler_in_heredoc);
				// signal(SIGQUIT, SIG_IGN);
				int fd;
				char *line;

				// dup2(fd,0);

				fd = open("/tmp/", O_RDWR | O_CREAT | O_TRUNC, 0777);

				while (1)
				{
					signal(SIGQUIT, SIG_IGN);
					signal(SIGQUIT, handler_in_heredoc);

					line = readline(">");
					if (line == NULL)
					{
						return (1);
					}
					int len = 0;
					len = ft_strlen(list->f_name[1]) + 1;
					if (ft_strncmp(list->f_name[1], line,
							len) == 0)
					{
						break ;
					}

					write(fd, line, ft_strlen(line));
					write(fd, "\n", 1);
					free(line);
				}
				free(line);
				close(fd);

				exit(0);

				i++;
				}
			}
			else
			{
				wait(&g_exit_status);
				return (g_exit_status);
			}
		}
	}
	return (0);
}
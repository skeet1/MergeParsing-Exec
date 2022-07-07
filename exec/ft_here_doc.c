/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 07:14:58 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/01 09:06:32 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parse.h"
#include "../libft/libft.h"

//<< EOF without command
void	handler_in_heredoc(int sig)
{
	if (sig == SIGINT)
		exit(1);
}
int	heredoc_without_cmd( t_cmdl *list) //sigfault
{
	// printf(" delimter");
	int i = 0;
	if (ft_strncmp(list[list->cmd_iteration].type[i], "<<", 3) == 0)
		{
			// printf(" delimter  = %s \n",list[list->cmd_iteration].delimiter );
	if (fork() == 0)
	{
		//i must loop here
		// while(list[list->cmd_iteration].type[i] != NULL)
		// {
		
			// signal(SIGINT, handler_in_heredoc);
			// signal(SIGQUIT, SIG_IGN);
			int fd;
			char *line;
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
				int len  = 0;
				len = ft_strlen(list[list->cmd_iteration].delimiter) + 1;
				if (ft_strncmp(list[list->cmd_iteration].delimiter, line, len ) == 0)
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
	else
	{
		wait(&g_exit_status);
			return (g_exit_status);

	}
}
return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 07:14:58 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/13 08:07:15 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "../parsing/parse.h"

void	handler_in_heredoc(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	exit(EXIT_FAILURE);
}

void	sigg(int sig)
{
	if (sig == SIGINT)
		printf("\n");
}

int	heredoc_exec_part1(t_cmd *list, int i)
{
	int		id;
		int fd;
	char	*line;
	int		len;

	id = fork();
	if (id == -1)
		return (0);
	if (id == 0)
	{
		line = NULL;
		fd = open("/tmp/tmpherdoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		while (1)
		{
			signal(SIGINT, handler_in_heredoc);
			line = readline(">");
			if (!line)
				exit(EXIT_SUCCESS);
			len = 0;
			len = ft_strlen(list->f_name[i]) + 1;
			if (ft_strncmp(line, list->f_name[i], len) == 0)
			{
				break ;
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
		free(line);
		close(fd);
		exit(SUCCESSFUL);
	}
	else
	{
		waitpid(id, &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		return (g_exit_status);
	}
}
int	heredoc_exec(t_cmd *list)
{
	int	i;

	i = 0;
	while (list)
	{
		while (list->f_type[i])
		{
			if (list->f_type[i] == RED_IN_APP)
			{
				if (heredoc_exec_part1(list, i) == EXIT_FAILURE)
					return (UNSUCCESSFUL);
			}
			i++;
		}
		list = list->next;
	}
	return (SUCCESSFUL);
}

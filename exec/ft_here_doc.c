/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 07:14:58 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/13 21:18:18 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "../parsing/parse.h"

void	sigg(int sig)
{
	if (sig == SIGINT)
		printf("\n");
}

int	heredoc_exec_part1(t_cmd *list, int i)
{
	int		id;
	int		fd;
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
				break ;
			heredoc_write_fd(line, fd);
		}
		heredoc_exec_clean(line, fd);
	}
	else
		return (heredoc_wait(id));
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
				if (heredoc_exec_part1(list, i) == UNSUCCESSFUL)
					return (UNSUCCESSFUL);
			}
			i++;
		}
		i = 0;
		list = list->next;
	}
	return (SUCCESSFUL);
}

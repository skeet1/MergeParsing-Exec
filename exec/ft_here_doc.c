/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 07:14:58 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/17 11:25:39 by atabiti          ###   ########.fr       */
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

int	heredoc_exec_part1(t_cmd *cmds, int i, int id, int len)
{
	int		fd;
	char	*line;

	id = fork();
	if (id == -1)
		return (UNSUCCESSFUL);
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
			len = ft_strlen(cmds->f_name[i]) + 1;
			if (ft_strncmp(line, cmds->f_name[i], len) == 0)
				break ;
			heredoc_write_fd(line, fd);
		}
		heredoc_exec_clean(line, fd);
	}
	return (heredoc_wait(id));
}

int	heredoc_exec(t_cmd *cmds)
{
	int	i;
	int	id;
	int	len;

	i = 0;
	len = 0;
	id = 0;
	while (cmds)
	{
		while (cmds->f_type[i])
		{
			if (cmds->f_type[i] == RED_IN_APP)
			{
				if (heredoc_exec_part1(cmds, i, id, len) == UNSUCCESSFUL)
					return (UNSUCCESSFUL);
			}
			i++;
		}
		i = 0;
		cmds = cmds->next;
	}
	return (SUCCESSFUL);
}

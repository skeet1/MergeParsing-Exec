/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 08:29:00 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/17 12:50:09 by atabiti          ###   ########.fr       */
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

void	heredoc_exec_clean(char *line, int fd)
{
	free(line);
	close(fd);
	exit(SUCCESSFUL);
}

void	heredoc_write_fd(char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
}

int	heredoc_wait(int id)
{
	waitpid(id, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	return (g_exit_status);
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_exit_status = 1;
	}
}

void	signal_init(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, &handler);
}

void	voidthem(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

void	checkline(t_data data)
{
	if (data.cmd_line == NULL)
	{
		write(1, "exit\n", 6);
		exit(0);
	}
}
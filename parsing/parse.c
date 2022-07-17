/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:47:50 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/17 12:17:32 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "parse.h"

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

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*c;

	c = *cmd;
	while (c)
	{
		if (c->cmd)
			free(c->cmd);
		if (c->f_name)
			free(c->f_name);
		if (c->f_type)
			free(c->f_type);
		c = c->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_token	*token;
	t_cmd	*cmd;
	int		pipenbr;
	t_lis	*envp;

	(void)argc;
	(void)argv;
	pipenbr = 0;
	envp = copyenv(NULL, env);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
		signal(SIGINT, &handler);
		token = NULL;
		cmd = NULL;
		data.cmd_line = readline(PROMPT);
		add_history(data.cmd_line);
		if (data.cmd_line == NULL)
		{
			write(1, "exit\n", 6);
			exit(0);
		}
		data.cmd_line = ft_strtrim(data.cmd_line, " ");
		if (ft_strlen(data.cmd_line))
		{
			token = ft_token(token, &data, data.cmd_line);
			exp_change_value(envp, token);
			cmd = node_per_cmd(token);
		}
		if (data.cmd_line != NULL && data.error == 0 && cmd != NULL)
		{
			pipenbr = data.side;
			pass_to_exec(envp, cmd);
		}
		free(data.cmd_line);
		free_cmd(&cmd);
	}
	free_environ(envp);
	return (0);
}

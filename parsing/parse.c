/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:47:50 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/17 12:50:39 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "parse.h"

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

void	run(t_data data, t_lis *envp, t_cmd *cmd)
{
	int	pipenbr;

	pipenbr = 0;
	if (data.cmd_line != NULL && data.error == 0 && cmd != NULL)
	{
		pipenbr = data.side;
		pass_to_exec(envp, cmd);
	}
	free(data.cmd_line);
	free_cmd(&cmd);
}

void	parseit(t_data data, t_lis *envp, t_cmd *cmd, t_token *token)
{
	if (ft_strlen(data.cmd_line))
	{
		token = ft_token(token, &data, data.cmd_line);
		exp_change_value(envp, token);
		cmd = node_per_cmd(token);
	}
	run(data, envp, cmd);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_token	*token;
	t_cmd	*cmd;
	t_lis	*envp;

	voidthem(argc, argv);
	envp = copyenv(NULL, env);
	while (1)
	{
		signal_init();
		token = NULL;
		cmd = NULL;
		data.cmd_line = readline(PROMPT);
		add_history(data.cmd_line);
		checkline(data);
		data.cmd_line = ft_strtrim(data.cmd_line, " ");
		parseit(data, envp, cmd, token);
	}
	free_environ(envp);
	return (0);
}

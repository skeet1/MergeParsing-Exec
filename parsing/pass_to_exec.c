/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:34:10 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/06 20:27:19 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parse.h"
int	strlen_list(t_token *token, int pipenbr, t_cmdl *cmd)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == 10)
		{
			i++;
		}
		token = token->next;
	}
	return (i);
}

int	fill_cmd(t_token *token, int pipenbr, t_cmdl *cmd)
{
	int	i;

	i = 0;
	i = strlen_list(token, pipenbr, cmd);
	// printf(" args NB %d   \n", i);
	cmd->args = (char **)malloc(sizeof(char *) * (i + 1));
	// cmd->type =  (char **)malloc(sizeof(char *) * (i + 1));
	cmd->file =  (char **)malloc(sizeof(char *) * (i + 1));
		cmd->type =  (char **)malloc(sizeof(char *) * (i + 1));


	i = 0;
	while (token)
	{
		if (token->type == 9)
		{
			cmd[cmd->cmd_iteration].cmd = token->value;

			printf(" cmd  %s   \n", cmd[cmd->cmd_iteration].cmd);
		}
		if (token->type == 10)
		{
			cmd[cmd->cmd_iteration].args[i] = token->value;
			printf(" args  %s        \n \n", cmd[cmd->cmd_iteration].args[i]);
			i++;
		}
		if (token->type == 2)
		{
					token = token->next;

			cmd->file[i] = token->value;
						printf(" FILE IN  %s        \n \n", cmd->file[i]);

		}
			if (token->type == 3)
		{
									cmd->type[i] = token->value;

					token = token->next;

			cmd->file[i] = token->value;
			i++;

						// printf(" FILE OUT %s  type is  %s        \n \n", cmd->file[i], cmd->type[i]);

		}
		token = token->next;
	}
	cmd->type[i] = NULL;
	cmd[cmd->cmd_iteration].args[i] = NULL;
	return (0);
}
int	pass_to_exec(t_token *token, int pipenbr, struct s_envp *envp)
{
	t_cmdl	*cmd;
	int		itre;
	int		args;

	itre = 0;
	args = 0;
	// printf("pipe nb %d cmd nbr %d\n", pipenbr - 1, pipenbr );
	// print_token(token);
	cmd = (t_cmdl *)malloc(sizeof(t_cmdl) * (pipenbr));
	fill_cmd(token, pipenbr, cmd);
	cmd->cmd_nbr = pipenbr;
	cmd->there_is_pipe = pipenbr - 1;
	cmd->fd_out = 1;
	cmd->cmd_iteration = 0;
	if (cmd->cmd_nbr == 1 && cmd[0].cmd != NULL)
	{
		// heredoc_without_cmd(cmd);
		one_cmd(cmd, envp);
		free2d(cmd->args);
		
	}
	// else if (cmd->cmd_nbr > 1)
	// {
	// 	//problem wc  | ls ? in bash ls is printing first and problem in  wc | ls when unset the PATH it must shot 2 errors not one
	// 	// grep 1337 exec/*.c problem
	// 	ft_pipe(cmd, envp);
	// }
	return (0);
}

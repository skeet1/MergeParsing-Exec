/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:34:10 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/07 19:40:11 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parse.h"

int	strlen_list(t_token *token, int pipenbr, t_cmdl *cmd)
{
	int	i;

	i = 0;
	if (token == NULL)
		return (0);
		
	while (token)
	{
		
		if (token->type == 10)
		{
			i++;
		}
		if(token->type == 6)
		{
			break;
				return (i);
			
		}
		token = token->next;
	}
	return (i);
}
int	file_list(t_token *token, int pipenbr, t_cmdl *cmd)
{
	int	i;

	i = 0;
	if (token == NULL)
		return (0);
	while (token)
	{
		if (token->type == 7)
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
	int	args;
	int	file;
	int	cmd_iteration;

	cmd_iteration = 0;
	i = 0;
	args = strlen_list(token, pipenbr, cmd);
	cmd->count_args = args;
	file = file_list(token, pipenbr, cmd);
	cmd->file = (char **)malloc(sizeof(char *) * (file + 1));
	cmd->type = (char **)malloc(sizeof(char *) * (file + 1));
	cmd->count_redire = file;
	cmd[cmd_iteration].args = (char **)malloc(sizeof(char ) * (args + 1));
	cmd->cmd_nbr = 0;
		printf("ARGS = %d \n",args );
			args = strlen_list(token, pipenbr, cmd);
		printf("ARGS = %d \n",args );

		// print_token(token);
	args = 0;
	cmd[cmd_iteration].type[i] = "";
	// while (token != NULL)
	// {
	// 	if (token->type == CMD)
	// 	{
	// 		cmd[cmd_iteration].cmd = token->value;
	// 		cmd->cmd_nbr++;
	// 		printf("cmd   = %s\n\n\n", cmd[cmd_iteration].cmd );
	// 	}
	// 	if (token->type == ARG)
	// 	{
	// 		cmd[cmd_iteration].args[args] = token->value;
	// 					printf("args   = %s\n\n\n", cmd[cmd_iteration].args[args] );

	// 		args++;
	// 		// cmd[cmd_iteration].args[args] = NULL;
	// 	}
	// 	if (token->type == RED_OUT)
	// 	{
	// 		cmd[cmd_iteration].type[i] = token->value;
	// 		token = token->next;
	// 		cmd[cmd_iteration].file[i] = token->value;
	// 		i++;
	// 	}
	// 	if (token->type == RED_IN)
	// 	{
	// 		cmd[cmd_iteration].type[i] = token->value;
	// 		token = token->next;
	// 		cmd[cmd_iteration].file[i] = token->value;
	// 		i++;
	// 	}
	// 	if (token->type == RED_IN)
	// 	{
	// 		cmd[cmd_iteration].type[i] = token->value;
	// 		token = token->next;
	// 		cmd[cmd_iteration].file[i] = token->value;
	// 		i++;
	// 	}
	// 	if (token->type == RED_OUT_APP)
	// 	{
	// 		cmd[cmd_iteration].type[i] = token->value;
	// 		token = token->next;
	// 		cmd[cmd_iteration].file[i] = token->value;
	// 		i++;
	// 	}
	// 	if (token->type == RED_IN_APP)
	// 	{
	// 		cmd[cmd_iteration].type[i] = token->value;
	// 		token = token->next;
	// 		cmd[cmd_iteration].delimiter = token->value;
	// 		// wc << d
	// 		i++;
	// 	}
	// 	if (token->type == PIPE)
	// 	{
	// 		cmd_iteration++;
	// 		i = 0;
	// 		args = 0;
	// 			cmd->count_args = args;
	// // cmd[cmd_iteration].file = (char **)malloc(sizeof(char *) * (2));
	// // cmd[cmd_iteration].type = (char **)malloc(sizeof(char *) * (2));

	// // 		// wc << d
	// // 			cmd[cmd_iteration].args = (char **)malloc(sizeof(char ) * (12));

	// 	}
	// 	token = token->next;
	// }
	return (0);
}
void	free_it(t_cmdl *cmd, t_token *token, int pipenbr)
{
	int	i;
	int	args;
	int	x;

	i = 0;
	args = strlen_list(token, pipenbr, cmd);
	while (i < cmd->cmd_nbr)
	{
		x = 0;
		while (x < args)
		{
			free(cmd[i].args[x]);
			x++;
		}
			free(cmd[i].cmd);
		free(cmd[i].args);
		i++;
	}
	free(cmd);
}

int	pass_to_exec(t_token *token, int pipenbr, struct s_envp *envp)
{
	t_cmdl	*cmd;
	int		itre;
	int		args;

	cmd = NULL;
	itre = 0;
	args = 0;
	// printf("pipe nb %d cmd nbr %d\n", pipenbr - 1, pipenbr );
	// print_token(token);
	cmd = (t_cmdl *)malloc(sizeof(t_cmdl) * (pipenbr + 1));
	cmd->cmd_nbr = 0;
	fill_cmd(token, pipenbr, cmd);
	cmd->there_is_pipe = pipenbr - 1;
	cmd->fd_out = 1;
	cmd->cmd_iteration = 0;
	// printf("cmd nbr %d \n", cmd->cmd_nbr);
	// if (cmd->cmd_nbr == 0)
	// {
	// 	heredoc_without_cmd(cmd);
	// 	if (redirections(cmd) == 3)
	// 		return (3);
	// }
	// if (cmd->cmd_nbr == 1 && cmd[0].cmd != NULL)
	// {
	// 	// heredoc_without_cmd(cmd);
	// 	one_cmd(cmd, envp);
	// 	free2d(cmd->args);
				

	// 		// free_it(cmd, token, pipenbr);

	// }
	// else if (cmd->cmd_nbr > 1)
	// {
	// 	//problem wc  | ls ? in bash ls is printing first and problem in  wc | ls when unset the PATH it must shot 2 errors not one
	// 	// grep 1337 exec/*.c problem
	// 	ft_pipe(cmd, envp);
	// 			free2d(cmd->args);

	// 		// free_it(cmd, token, pipenbr);

	// }
	return (0);
}

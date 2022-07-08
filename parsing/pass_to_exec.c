/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:34:10 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/07 22:42:02 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parse.h"

void	num_of_rd(t_token *token, t_cmdl *cmd)
{
	t_token	*tok;
	int		arg_num;
	int		files;

	files = 0;
	while (token)
	{
		arg_num = 0;
		if (token != NULL)
		{
			tok = token;
			while (tok)
			{
				if (tok->type == 2 || tok->type == 3 || tok->type == 4
					|| tok->type == 5)
					arg_num++;
				if (tok->type == FILEE)
					files++;
				else if (tok->type == PIPE)
					break ;
				tok = tok->next;
			}
		}
		token->redi = arg_num;
		token->files = files;
		token = token->next;
	}
}
void	num_of_args(t_token *token, t_cmdl *cmd)
{
	t_token	*tok;
	int		arg_num;

	while (token)
	{
		arg_num = 0;
		if (token->type == CMD)
		{
			tok = token;
			while (tok)
			{
				if (tok->type == ARG)
					arg_num++;
				else if (tok->type == PIPE)
					break ;
				tok = tok->next;
			}
		}
		token->args_num = arg_num;
		token = token->next;
	}
}

void	loop(t_token *token, int pipenbr, t_cmdl *cmd)
{
	int	cmd_iteration;

	cmd_iteration = 0;
	while (token)
	{
		if (token->type == 9)
		{
			num_of_args(token, cmd);
			printf("ARGS %d \n", token->args_num);
			cmd[cmd_iteration].args = (char **)malloc(sizeof(char)
					* (token->args_num + 1));
		}
		if (token->type == 2 || token->type == 3 || token->type == 4
			|| token->type == 5)
		{
			num_of_rd(token, cmd);
			printf("FILES %d \n", token->files);
			// cmd[cmd_iteration].count_redire = token->redi;
			// cmd[cmd_iteration].type = (char **)malloc(sizeof(char *)
			// 		* (cmd[cmd_iteration].count_redire + 1));
			// cmd[cmd_iteration].file = (char **)malloc(sizeof(char *)
			// 		* (cmd[cmd_iteration].count_redire + 1));
		}
		token = token->next;
	}
}
int	fill_cmd(t_token *token, int pipenbr, t_cmdl *cmd)
{
	int	i;
	int	args;
	int	file;
	int	cmd_iteration;

	cmd_iteration = 0;
	cmd->cmd_nbr = pipenbr - 1;
	cmd[cmd_iteration].count_args = 0;
	loop(token, pipenbr, cmd);
	i = 0;
	cmd->cmd_nbr = 0;
	cmd->count_redire = 0;
	args = 0;
	// 	while (token != NULL)
	// 	{
	// 		if (token->type == CMD)
	// 		{
	// 			cmd[cmd_iteration].cmd = token->value;
	// 			cmd->cmd_nbr++;
	// 			// printf("cmd   = %s\n\n\n", cmd[cmd_iteration].cmd );
	// 		}
	// 		if (token->type == ARG)
	// 		{
	// 			cmd[cmd_iteration].args[args] = token->value;
	// 			// printf("args   = %s\n\n\n", cmd[cmd_iteration].args[args] );
	// 			args++;
	// 			// cmd[cmd_iteration].args[args] = NULL;
	// 		}
	// 		if (token->type == RED_OUT)
	// 		{
	// 			cmd[cmd_iteration].type[i] = token->value;
	// 			token = token->next;
	// 			cmd[cmd_iteration].file[i] = token->value;
	// 			i++;
	// 		}
	// 		if (token->type == RED_IN)
	// 		{
	// 			cmd[cmd_iteration].type[i] = token->value;
	// 			token = token->next;
	// 			cmd[cmd_iteration].file[i] = token->value;
	// 			i++;
	// 		}
	// 		if (token->type == RED_IN)
	// 		{
	// 			cmd[cmd_iteration].type[i] = token->value;
	// 			token = token->next;
	// 			cmd[cmd_iteration].file[i] = token->value;
	// 			i++;
	// 		}
	// 		if (token->type == RED_OUT_APP)
	// 		{
	// 			cmd[cmd_iteration].type[i] = token->value;
	// 			token = token->next;
	// 			cmd[cmd_iteration].file[i] = token->value;
	// 			i++;
	// 		}
	// 		if (token->type == RED_IN_APP)
	// 		{
	// 			cmd[cmd_iteration].type[i] = token->value;
	// 			token = token->next;
	// 			cmd[cmd_iteration].delimiter = token->value;
	// 			// wc << d
	// 			i++;
	// 		}
	// 		if (token->type == PIPE)
	// 		{
	// 			cmd_iteration++;
	// 			i = 0;
	// 			args = 0;
	// 			// cmd->count_args = args;
	// 		}
	// 		token = token->next;
	// 	}
	// 	return (0);
	// }
	// void	free_it(t_cmdl *cmd, t_token *token, int pipenbr)
	// {
	// 	int	i;
	// 	int	x;
	// 	i = 0;
	// 	// args = strlen_list(token, pipenbr, cmd);
	// 	while (i < cmd->cmd_nbr)
	// 	{
	// 		x = 0;
	// 		while (x < cmd[i].count_args)
	// 		{
	// 			free(cmd[i].args[x]);
	// 			x++;
	// 		}
	// 		free(cmd[i].cmd);
	// 		free(cmd[i].args);
	// 		i++;
	// 	}
	// 	free(cmd);
	return (0);
}

int	pass_to_exec(t_token *token, int pipenbr, struct s_envp *envp)
{
	t_cmdl	*cmd;
	int		itre;
	int		args;

	cmd = NULL;
	itre = 0;
	args = 0;
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
	// if (cmd->cmd_nbr == 1)
	// {
	// 	// heredoc_without_cmd(cmd);
	// 	one_cmd(cmd, envp);
	// 	// free2d(cmd->args);
	// 	free_it(cmd, token, pipenbr);
	// }
	// else if (cmd->cmd_nbr > 1)
	// {
	// 	//problem wc  | ls ? in bash ls is printing first and problem in  wc | ls when unset the PATH it must shot 2 errors not one
	// 	// grep 1337 exec/*.c problem
	// 	ft_pipe(cmd, envp);
	// 			// free2d(cmd->args);
	// 		// free_it(cmd, token, pipenbr);
	// }
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:34:10 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/08 19:47:39 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parse.h"

void	free_it(t_cmdl *cmd)
{
	int	i;
	int	x;

	i = 0;
	// args = strlen_list(token, pipenbr, cmd);
	while (i < cmd->cmd_nbr)
	{
		x = 0;
		while (cmd[i].count_args)
		{
			free(cmd[i].args[x]);
			x++;
		}
		free(cmd[i].cmd);
		free(cmd[i].args);
		i++;
	}
}

// void	num_of_rd(t_token *token, t_cmdl *cmd)
// {
// 	t_token	*tok;
// 	int		arg_num;
// 	int		files;

// 	files = 0;
// 	while (token)
// 	{
// 		arg_num = 0;
// 		if (token != NULL)
// 		{
// 			tok = token;
// 			while (tok)
// 			{
// 				if (tok->type == 2 || tok->type == 3 || tok->type == 4
// 					|| tok->type == 5)
// 					arg_num++;
// 				if (tok->type == FILEE)
// 					files++;
// 				else if (tok->type == PIPE)
// 					break ;
// 				tok = tok->next;
// 			}
// 		}
// 		token->redi = arg_num;
// 		token->files = files;
// 		token = token->next;
// 	}
// }
// void	num_of_args(t_token *token, t_cmdl *cmd)
// {
// 	t_token	*tok;
// 	int		arg_num;

// 	token->count_cmd = 0;
// 	while (token)
// 	{
// 		arg_num = 0;
// 		if (token->type == CMD)
// 		{
// 			tok = token;
// 			while (tok)
// 			{
// 				if (tok->type == ARG)
// 					arg_num++;
// 				else if (tok->type == PIPE)
// 					break ;
// 				tok = tok->next;
// 			}
// 		}
// 		token->args_num = arg_num;
// 		token = token->next;
// 	}
// }

// void	loop(t_token *token, int pipenbr, t_cmdl *cmd, int n)
// {
// 	int	cmd_iteration;
// 	int	done;
// 	int	i;

// 	done = 0;
// 	cmd_iteration = 0;
// 	num_of_rd(token, cmd);
// 	num_of_args(token, cmd);
// 	i = 0;
// 	// while (i < n)
// 	// 	token = token->next;
// 	i = 0;
// 	if (token->args_num)
// 	{
// 		printf("ARGS %d CMD NB %d \n", token->args_num, i);
// 		cmd[cmd_iteration].args = (char **)malloc(sizeof(char)
// 				* (token->args_num + 1));
// 	}
// 	else
// 	{
// 		cmd[cmd_iteration].args = (char **)malloc(sizeof(char) * (1));
// 		cmd[cmd_iteration].args[0] = NULL;
// 	}
// 	if (token->redi)
// 	{
// 		printf("RED %d CMD NB %d \n", token->redi, i);
// 		cmd[cmd_iteration].type = (char **)malloc(sizeof(char *) * (token->redi
// 					+ 1));
// 	}
// 	else
// 	{
// 		cmd[cmd_iteration].type = (char **)malloc(sizeof(char *) * (1));
// 		cmd[cmd_iteration].type[0] = NULL;
// 	}
// 	if (token->files)
// 	{
// 		printf("FILE %d CMD NB %d \n", token->files, i);
// 		cmd[cmd_iteration].file = (char **)malloc(sizeof(char *) * (token->files
// 					+ 1));
// 	}
// 	else
// 	{
// 		cmd[cmd_iteration].file = (char **)malloc(sizeof(char *) * (1));
// 		cmd[cmd_iteration].file[0] = NULL;
// 	}
// }

// int	fill_cmd(t_token *token, int pipenbr, t_cmdl *cmd)
// {
// 	int	i;
// 	int	args;
// 	int	file;
// 	int	cmd_iteration;

// 	cmd_iteration = 0;
// 	cmd->cmd_nbr = pipenbr - 1;
// 	i = 0;
// 	cmd->cmd_nbr = 0;
// 	cmd->count_redire = 0;
// 	args = 0;
// 	loop(token, pipenbr, cmd, cmd_iteration);
// 	while (token != NULL)
// 	{
// 		if (token->type == CMD)
// 		{
// 			cmd[cmd_iteration].cmd = token->value;
// 			cmd->cmd_nbr++;
// 		}
// 		if (token->type == ARG)
// 		{
// 			cmd[cmd_iteration].args[args] = token->value;
// 			args++;
// 		}
// 		if (token->type == RED_OUT || token->type == RED_IN
// 			|| token->type == RED_OUT_APP || token->type == RED_OUT_APP
// 			|| token->type == RED_IN_APP)
// 		{
// 			cmd[cmd_iteration].type[i] = token->value;
// 			token = token->next;
// 			cmd[cmd_iteration].file[i] = token->value;
// 			i++;
// 		}
// 		if (token->type == PIPE)
// 		{
// 			cmd_iteration++;
// 			i = 0;
// 			args = 0;
// 			loop(token, pipenbr, cmd, cmd_iteration);
// 		}
// 		token = token->next;
// 	}
// 	return (0);
// }
int	ft_lstsize(t_cmd *lst)
{
	int	lstlen;

	lstlen = 0;
	while (lst)
	{
		lst = lst->next;
		lstlen ++;
	}
	return (lstlen);
}
int	pass_to_exec(t_token *token, int pipenbr, struct s_envp *envp, 	t_cmd *cmds)
{
	t_cmdl	*cmd;

// print_cmd(cmds);
int nbr = ft_lstsize(cmds);
cmds->cmdnbr = 0;
	cmds->cmdnbr = nbr;
	// cmd = NULL;
	// itre = 0;
	// args = 0;
	// cmd = (t_cmdl *)malloc(sizeof(t_cmdl) * (pipenbr + 1));
	// cmd->cmd_nbr = 0;
	// cmd->count_args = 0;
	// cmd->count_files = 0;
	// cmd->count_redire = 0;
	// cmd->type = NULL;
	// cmd->file = NULL;
	// cmd->args = NULL;
	// fill_cmd(token, pipenbr, cmd);
	// cmd->there_is_pipe = pipenbr - 1;
	// cmd->fd_out = 1;
	// cmd->cmd_iteration = 0;
	// // printf("cmd nbr %d \n", cmd->cmd_nbr);
	// cmd->count_args = token->args_num;
	// cmd->count_files = token->files;
	// cmd->count_redire = token->redi;
	// if (cmd->cmd_nbr == 0)
	// {
	// 	heredoc_without_cmd(cmd);
	// 	if (redirections(cmd, token) == 3)
	// 		return (3);
	// }
	cmds->fd_out = 0;
	if (nbr == 1)
	{
		one_cmd(cmd, envp, token, cmds);
		// free2d(cmd->args);
		// free_it(cmd, token, pipenbr);
	}
	// else if (cmd->cmd_nbr > 1)
	// {
	// 	//problem wc  | ls ? in bash ls is printing first and problem in  wc | ls when unset the PATH it must shot 2 errors not one
	// 	// grep 1337 exec/*.c problem
	// 	ft_pipe(cmd, envp);
	// 	// free2d(cmd->args);
	// 	// free_it(cmd, token, pipenbr);
	// }
	// // free_it(cmd);
	// free2d(cmd->args);
	// free2d(cmd->type);
	// free2d(cmd->file);
	return (0);
}

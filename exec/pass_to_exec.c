/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:34:10 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/08 21:28:05 by atabiti          ###   ########.fr       */
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
		one_cmd( envp, token, cmds);
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

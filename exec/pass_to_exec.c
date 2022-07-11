/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:34:10 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/11 09:46:31 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parse.h"

// void	free_it(t_cmdl *cmd)
// {
// 	int	i;
// 	int	x;

// 	i = 0;
// 	// args = strlen_list(token, pipenbr, cmd);
// 	while (i < cmd->cmd_nbr)
// 	{
// 		x = 0;
// 		while (cmd[i].count_args)
// 		{
// 			free(cmd[i].args[x]);
// 			x++;
// 		}
// 		free(cmd[i].cmd);
// 		free(cmd[i].args);
// 		i++;
// 	}
// }

int	ft_lstsize(t_cmd *lst)
{
	int	lstlen;

	lstlen = 0;
	while (lst)
	{
		lst = lst->next;
		lstlen++;
	}
	return (lstlen);
}
int	pass_to_exec(struct s_envp *envp, t_cmd *cmds)
{
	int	nbr;

	print_cmd(cmds);
					ft_init(cmds);

	nbr = ft_lstsize(cmds);
	cmds->cmdnbr = nbr;

	if (nbr == 1)
	{
		
		one_cmd(envp, cmds);
	}
	else if (cmds->cmdnbr > 1)
	{
		//problem wc  | ls ? in bash ls is printing first and problem in
		//wc | ls when unset the PATH it must shot 2 errors not one
		// grep 1337 exec/*.c problem
		ft_pipe(cmds, envp);
		// free2d(cmd->args);
		// free_it(cmd, token, pipenbr);
	}
	// // free_it(cmd);
	// free2d(cmd->args);
	// free2d(cmd->type);
	// free2d(cmd->file);
	return (0);
}


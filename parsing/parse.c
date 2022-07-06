/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:47:50 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/06 10:38:07 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../minishell.h"
#include "../libft/libft.h"

int	main(int argc, char **argv,  char **env)
{
	t_data	data;
	t_token	*token;
			t_cmdl *cmd;
	struct						s_envp * envp;
	envp = (struct	s_envp *)malloc((1) * sizeof(	struct	s_envp));
	int itre = 0;
	int args = 0 ;
				// cmd = (t_cmdl *)malloc(sizeof(t_cmdl) * (data.side - 1));
				// cmd->args = malloc(sizeof(char *) * 10);
// 				/////
 ft_copy_1st_env(envp, env);
	if (argc == 1)
	{
		while (1)
		{
			token = NULL;
			data.cmd_line = readline(PROMPT);
			add_history(data.cmd_line);
			data.cmd_line = ft_strtrim(data.cmd_line, " ");
			if (ft_strlen(data.cmd_line))
				token = ft_token(token, &data, data.cmd_line);
					pass_to_exec(token);

////
	// 		while (token)
	// {
	// 	if(token->type == 8 && itre == 0)
	// 	{
	// 		cmd->cmd =  token->value;
				
					
	// 				printf("CMD is %s\t\n",cmd[itre].cmd);


	// 	}
	// 			if(token->type == 8 && itre > 0)
	// 			{
					

	// 					cmd->args[itre] = strdup( token->value);
				
	// 				printf("ARGS is %s\t\n",cmd->args[itre]);
	// 				args++;

	// 			}



	// 		itre++;
	// 	token = token->next;
	// }

	// cmd->cmd_nbr = 1;
	// 						cmd->there_is_pipe = 0;
	// printf("%d\n", args);

	// cmd->cmd_iteration = 0;
	// 		if (cmd->cmd_nbr == 1 && cmd[0].cmd != NULL)
	// 		{
	// 			// heredoc_without_cmd(cmd);

	// 			one_cmd(cmd, envp);
	// 		}
	// 		else if(cmd->cmd_nbr > 1)
	// 		{
	// 			//problem wc  | ls ? in bash ls is printing first and problem in  wc | ls when unset the PATH it must shot 2 errors not one
	// 			// grep 1337 exec/*.c problem
	// 			ft_pipe(cmd, envp);
	// 		}
	// ////
		}
	}
}
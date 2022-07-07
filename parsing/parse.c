/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:47:50 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/07 14:30:08 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "parse.h"

void	mark_cmd(t_token *tok)
{
	t_token	*token;
	int		pipe;
int ssdd;
	pipe = 1;
	token = tok;
	while (token)
	{
		if (pipe && token->type == WORD)
		{
			token->type = CMD;
			pipe = 0;
		}
		else if (token->type == WORD)
			token->type = ARG;
		else if (token->type == PIPE)
			pipe = 1;
		token = token->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data data;
	t_token *token;
	struct s_envp *envp;
	envp = (struct s_envp *)malloc((1) * sizeof(struct s_envp));
	int pipenbr = 0;
	ft_copy_1st_env(envp, env);
	if (argc == 1)
	{
		while (1)
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, handler);
			token = NULL;
			data.cmd_line = readline(PROMPT);
			add_history(data.cmd_line);
			if(data.cmd_line == NULL)
			{
				exit(1);
			}
			data.cmd_line = ft_strtrim(data.cmd_line, " ");
						add_history(data.cmd_line);

			if (ft_strlen(data.cmd_line))
			{
				token = ft_token(token, &data, data.cmd_line);
				mark_cmd(token);
			}
			// print_token(token);
			if(data.cmd_line != NULL)
			{
				pipenbr = data.side;
				pass_to_exec(token, pipenbr, envp);
			}
					free(	data.cmd_line);

		}
	}
	
	return 0;
}

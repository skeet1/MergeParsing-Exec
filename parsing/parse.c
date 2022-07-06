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

#include "../libft/libft.h"
#include "../minishell.h"
#include "parse.h"

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
			data.cmd_line = ft_strtrim(data.cmd_line, " ");
			if (ft_strlen(data.cmd_line))
				token = ft_token(token, &data, data.cmd_line);
			pipenbr = data.side;
			pass_to_exec(token, pipenbr, envp);
		}
	}
}
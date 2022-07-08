/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:47:50 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/08 13:34:32 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "parse.h"

void	mark_cmd(t_token *tok)
{
	t_token	*token;
	int		pipe;
	int 	ssdd;
	
	pipe = 1;
	token = tok;
	while (token)
	{
		token->args_num = 0;
		if (pipe && token->type == WORD)
		{
			token->type = CMD;
			int	i = -1;
			while (token->value[++i])
				token->value[i] = ft_tolower(token->value[i]);
			pipe = 0;
		}
		else if (token->type == WORD)
			token->type = ARG;
		else if (token->type == PIPE)
			pipe = 1;
		token = token->next;
	}
}

void	exp_change_value(struct s_envp *envp, t_token *token)
{
	struct s_envp	*env;
	int				i;
	int				len;
	
	len = 0;
	// printf("change value\n");
	// while (token)
	// {
	// 	i = 0;
	// 	env = envp;
	// 	len = (int)ft_strlen(ft_strchrr(token->value, '$'));
	// 	if (token->type == WORD && !token->sgl_qt)
	// 	{
	// 		while (i < env->envpitems)
	// 		{
	// 			// if (ft_strncmp(ft_strchrr(token->value, '$'), env->name[i], len) == 0)
	// 			// {
	// 				// printf("%s\t", env->name[i]);
	// 				// printf("len is: %d\t", len);
	// 				printf("before: %s\t", token->value);
	// 				// printf("before CHR: %s\n", ft_strchrr(token->value, '$'));
	// 				// printf("dif is %d\n", ft_strncmp(env->name[i], ft_strchrr(token->value, '$'), len));
	// 				if (ft_strncmp(env->name[i], ft_strchrr(token->value, '$'), len) == 0)
	// 				{
	// 					token->value = env->value[i];
	// 				// token->value = env->value[i];
	// 					printf("After: %s\n", token->value);
	// 				}	
	// 			// }
	// 			// printf("%d\n", ft_strlen(ft_strchrr(token->value, '$')));
	// 			// printf("%s\n", ft_strchrr(token->value, '$'));
	// 			// if (ft_strchrr(token->value, '$') == env->name[i])
	// 			// 	printf("found\n");
	// 			i++;
	// 		}
	// 	}
	// 	token = token->next;
	// }
}

void	node_per_cmd(t_token *token)
{
	char	**args;
	int		*file_type;
	char	**file_name;
	int		i[2];
	int a;
	int	ft;
	t_token *tok;

	a = 0;
	ft = 0;
	i[0] = 0;
	i[1] = 0;
	while (token)
	{
		tok = token;
		while (tok && tok->type != PIPE)
		{
			if (tok->type == WORD)
				a++;
			else if (tok->type == FILEE)
				ft++;
			tok = tok->next;
		}
		args = malloc(sizeof(char *) * a);
		file_name = malloc(sizeof(char *) * ft);
		file_type = malloc(sizeof(int) * ft);
		while (token)
		{
			while (token && token->type != PIPE)
			{
				if (token->type == WORD)
					args[i[0]++] = token->value;
				else if (token->type >= 2 && token->type <= 5)
				{
					file_type[i[1]] = tok->type;
					token = token->next;
					file_name[i[1]++] = token->value;
				}
			}
		}
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
			if (ft_strlen(data.cmd_line))
			{
				token = ft_token(token, &data, data.cmd_line);
				// exp_change_value(envp, token);
				printf("here main\n");
				// node_per_cmd(token);
				mark_cmd(token);
			}
			print_token(token);
			// if(data.cmd_line != NULL && data.error == 0 && token != NULL)
			// {
			// 	pipenbr = data.side;
			// 	pass_to_exec(token, pipenbr, envp);
			// }
			// 		free(	data.cmd_line);

		}
	}
	return (0);
}

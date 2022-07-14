/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:47:50 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/14 10:49:41 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "parse.h"
void	handler(int sig)
{
	if (sig == SIGINT)
	{
				printf("\n");
		rl_on_new_line();      

		rl_replace_line("", 1);

		rl_redisplay();
		g_exit_status = 1;  
	}
}
void	mark_cmd(t_token *tok)
{
	t_token	*token;
	int		pipe;
	
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

char	*rm_first_char(char *str)
{
	char	*s;
	int		len;
	int		i;
	
	if (str)
	{
		len = ft_strlen(str);
		s = (char *)malloc(len);
		if (!s)
			return (s);
		i = 0;
		if (str[i])
			i++;
		while (str[i])
		{
			s[i - 1] = str[i];
			i++;
		}
		s[i - 1] = '\0';
		return (s);
	}
	return (NULL);
}

void	exp_change_value(struct s_envp *envp, t_token *token)
{
	struct s_envp	*env;
	int				i;
	int				len;
	
	len = 0;
	while (token)
	{
		if (token->type == WORD && !token->sgl_qt)
		{
			i = 0;
			while (envp->name[i])
			{
				if (ft_strcmp(rm_first_char(ft_strchr(token->value, '$')), envp->name[i]) == 0)
				{
					token->value = envp->value[i];
				}
				i++;
			}
		}
		token = token->next;
	}
}

t_cmd	*new_node_cmd(char **args, int *file_type, char **file_name)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (new);
	new->cmd = args;
	new->f_name = file_name;
	new->f_type = file_type;
	new->next = NULL;
	return (new);
}

void	add_back_cmd(t_cmd **cmd, char **args, int *file_type, char **file_name)
{
	t_cmd	*last;
	t_cmd	*new;

	new = new_node_cmd(args, file_type, file_name);
	last = *cmd;
	if (new == NULL)
		return ;
	if (last == NULL)
	{
		*cmd = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
}

t_cmd	*node_per_cmd(t_token *token)
{
	char	**args;
	int		*file_type;
	char	**file_name;
	int		i[2];
	int a;
	int	ft;
	t_token *tok;
	t_cmd 	*cmd;

	cmd = NULL;
	while (token)
	{
		a = 0;
		ft = 0;
		i[0] = 0;
		i[1] = 0;
		tok = token;
		while (tok && tok->type != PIPE)
		{
			if (tok->type == WORD)
				a++;
			else if (tok->type >= 2 && tok->type <= 5)
				ft++;
			tok = tok->next;
		}
		// printf("cmd is %d -- file is %d\n", a, ft);
		args = ft_calloc(sizeof(char *), a + 1);
		file_name = ft_calloc(sizeof(char *), ft + 1);
		file_type = ft_calloc(sizeof(int), ft + 1);
		while (token)
		{
			while (token && token->type != PIPE)
			{
				if (token->type == WORD)
				{
					// printf("mcd here : %s\n", token->value);
					args[i[0]++] = token->value;
				}
				else if (token->type >= 2 && token->type <= 5)
				{
					file_type[i[1]] = token->type;
				}
				else if (token->type == FILEE)
					file_name[i[1]++] = token->value;
				token = token->next;
			}
			break;
		}
		args[i[0]] = NULL;
		file_type[i[1]] = 0;
		file_name[i[1]] = NULL;
		add_back_cmd(&cmd, args, file_type, file_name);
		if (token)
			token = token->next;
	}
	return (cmd);
}

void	print_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		// printf("\ncmd  :  \n");
		int i = 0;
		while (cmd && cmd->cmd[i])
		{
			
			// printf("%s\n", cmd->cmd[i]);
			// printf("len =%d\n", ft_strlen(cmd->cmd[i]));
			cmd->count_args = i;
			i++;
		}
		// printf(" %d   \n\n", cmd->count_args);
		// i = 0;
		// while (cmd && cmd->f_name[i] && cmd->f_type[i])
		// {
		// 	printf("type is : %d -- name is : %s\n", cmd->f_type[i], cmd->f_name[i]);
		// 	i++;
		// }
		cmd = cmd->next;
	}
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd *c;

	c = *cmd;
	while (c)
	{
		if (c->cmd)
			free(c->cmd);
		if (c->f_name)
			free(c->f_name);
		if (c->f_type)
			free(c->f_type);
		c = c->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data data;
	t_token *token;
	struct s_envp *envp;
	t_cmd *cmd; 
	envp = (struct s_envp *)malloc((1) * sizeof(struct s_envp));
	int pipenbr = 0;
	ft_copy_1st_env(envp, env);
	if (argc == 1)
	{
		while (1)
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, &handler);
			cmd = NULL;
			
			
			token = NULL;
			cmd = NULL;
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
				cmd = node_per_cmd(token);
				// mark_cmd(token);
			}
			// print_cmd(cmd);
			// print_token(token);
			if(data.cmd_line != NULL && data.error == 0 && cmd != NULL)
			{
				pipenbr = data.side;
				pass_to_exec(envp, cmd);
			}
				free(	data.cmd_line);
			free_cmd(&cmd);
		}
		free2d(envp->name);
		free2d(envp->value);
				free2d(envp->environment);

		
	}
	return (0);
}

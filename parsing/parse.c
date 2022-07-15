/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:47:50 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/15 17:08:28 by atabiti          ###   ########.fr       */
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

char	*before_dol(char *str)
{
	int		i;
	char	*s;

	i = 0;
	while (str[i] && str[i] != '$')
	{
		i++;
	}
	s = malloc(i + 1);
	i = 0;
	while (str[i] && str[i] != '$')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	dolar_exist(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*rest_cmp(char *str, int len)
{
	char *s;
	
	s = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (!s)
		return (s);
	int i = 0;
	while (str[len + i])
	{
		s[i] = str[len + i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*rest_from_index(char *str, int ind)
{
	char	*s;
	int		i;

	i = 0;
	s = malloc(ft_strlen(str) - ind - 1);
	if (!s)
		return (s);
	while (str[ind + i + 2])
	{
		s[i] = str[ind + i + 2];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*before_index(char *str, int ind)
{
	int		i;
	char	*s;

	i = 0;
	s = malloc(sizeof(char) * (ind + 1));
	if (!s)
		return (s);
	while (i < ind)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

void	exp_exit_status(char **str)
{
	char *s;
	
	s = *str;
	int i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
			*str = ft_strjoin(ft_strjoin(before_index(s, i), ft_itoa(g_exit_status)), rest_from_index(s, i));
		i++;
	}
}

void	exp_change_value(struct s_environ *envp, t_token *token)
{
	struct s_environ	*env;
	char			**sp;
	int				len;
	
	len = 0;
	while (token)
	{
		if (token->type == WORD && !token->sgl_qt && dolar_exist(token->value))
		{
			exp_exit_status(&token->value);
			sp = ft_split(token->value, '$');
			int j = 0;
			while (sp[j])
			{
				env = envp;
				while (env)
				{
					if (ft_strncmp(sp[j], env->name, ft_strlen(env->name)) == 0)
					{
						token->value = ft_strjoin(before_dol(token->value), env->value);
						if (ft_strlen(env->name) != ft_strlen(sp[j]))
							token->value = ft_strjoin(token->value, rest_cmp(sp[j], ft_strlen(env->name)));
						break;
					}
					env = env->next;
				}
				j++;
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
	t_cmd *cmd; 
	int pipenbr = 0;
	struct s_environ *envp;
	envp = NULL;
	envp =	ftcopyenv(envp, env);
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
				write(1, "exit\n", 6);
							exit(0);
			}
			data.cmd_line = ft_strtrim(data.cmd_line, " ");
			if (ft_strlen(data.cmd_line))
			{
				token = ft_token(token, &data, data.cmd_line);
				exp_change_value(envp, token);
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
		// free2d(envp->name);
		// free2d(envp->value);
		// 		free2d(envp->environment);

		
	}
	return (0);
}

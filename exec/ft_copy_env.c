// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_copy_env.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/07/14 13:06:17 by atabiti           #+#    #+#             */
// /*   Updated: 2022/07/15 14:03:06 by atabiti          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */


// #include "../libft/libft.h"
// #include "../minishell.h"

// struct s_environ	*ftnewnode(char *envv)
// {
// 	struct s_environ	*new;

// 	new = (struct s_environ *)malloc(sizeof(struct s_environ));
// 	if (!new)
// 		return (new);
// 	new->env = envv;
// 	new->next = NULL;
// 	return (new);
// }

// void	ftaddback(struct s_environ **token, char *envv)
// {
// 	struct s_environ	*last;
// 	struct s_environ	*new;

// 	last = *token;
// 	new = ftnewnode(envv);
// 	if (new == NULL)
// 		return ;
// 	if (last == NULL)
// 	{
// 		*token = new;
// 		return ;
// 	}
// 	while (last->next != NULL)
// 	{
// 		last = last->next;
// 	}
// 	last->next = new;
// }

// struct s_environ *	ftsplitenv(struct s_environ *environ)
// {
	
// 	int	x;

// 	x = 0;
// 	int i = 0;
// 	while (environ != NULL)
// 	{
// 		while (environ->env[x] != '=' && environ->env[x] != '\0')
// 		{
// 			if (environ->env[x] == '=')
// 				break ;
// 			x++;
// 		}
// 		environ->name = ft_substr(environ->env, 0, x);
// 		environ->value = ft_substr(environ->env, x + 1, ft_strlen(environ->env) - x);
// 		x = 0;
// 		environ = environ->next;
// 	}
// 	return (environ);
// }

// void	print(struct s_environ *env)
// {
// 	while (env)
// 	{
// 		printf("FULL %s| NAME %s | VALUE %s \n", env->env,env->name, env->value);
// 		env = env->next;
// 	}
// }

// struct s_environ  *ft_copy_env(struct s_environ *environ, char **envp)
// {
// 	int i = 0;
// 		while (envp[i])
// 	{
// 				// printf("%s \n", envp[i]);
// 		ftaddback(&environ, envp[i]);
// 		i++;
// 	}
// 	environ->envpitems= i;
// 	ftsplitenv(environ);
// 		// print(environ);
// 	return (environ);

// }
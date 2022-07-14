/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:51:47 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/14 12:53:28 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
struct s_linked 
{
  char *env;
    struct s_linked *next;
};

typedef struct s_token
{
      char *env;
	struct s_token	*next;
}					t_token;

t_token	*ft_new_node(char *value)
{
	t_token *new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (new);
    new->env = value;
	new->next = NULL;
	return (new);
}

void	ft_add_back(t_token **token, char *value)
{
	t_token *last;
	t_token	*new;

	last = *token;
	new = ft_new_node(value);
	if (new == NULL)
		return ;
	if (last == NULL)
	{
		*token = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
}



void print(t_token* env)
{
     while(env)
    {         
         printf("%s\n", env->env);

        env = env->next;
    }
}

int main(int ac , char **av, char **envp)
{
    t_token *env;
    int i = 0;
    env = NULL;
    while (envp[i])
        i++;
    int x = 0;
    while(x < i)
    {
        if (x == i - 1)
        ft_add_back(&env,    envp[x] );
        x++;
    }
    
   print(env);
    return 0;    
}
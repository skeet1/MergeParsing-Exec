/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:56:03 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/06 10:42:26 by mkarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PROMPT "minishell $ "
# define PRE_ERR "minishell: "
# define SNT_ERR "minishell: syntax error near unexpected token `"

typedef enum e_token
{
	S_QUOTE,
	D_QUOTE,
	RED_IN,
	RED_OUT,
	RED_IN_APP,
	RED_OUT_APP,
	PIPE,
	FILEE,
	WORD,
	CMD,
	ARG
}					t_e_token;

/* ----------- START STRUCT FOR SPLIT ----------- */

// typedef struct s_variables
// {
// 	int		l;
// 	int		i;
// 	int		j;
// 	int		cl;
// }			t_variables;

/* ----------- END STRUCT FOR SPLIT ----------- */

typedef struct s_data
{
	char			*cmd_line;
	int				side;
	char			**cmd_sides;
}					t_data;

typedef struct s_token
{
	int				type;
	char			*value;
	int				dbl_st;
	struct s_token	*next;
}					t_token;

typedef struct s_files
{
	int				type;
	char			*name;
	struct s_files	*next;
}					t_files;

// size_t	ft_strlen(char *s);
void				ft_putstr(char *s);
void				ft_putendl(char *s);

// typedef struct s_cmdl {
// 	char	*cmd;
// 	char	**args;
// 	char	*in_red;
// 	char	*out_red;
// }		t_cmdl;

typedef struct t_cmdl
{
	char			*cmd;
	char			**args;
	char			*in_red;
	char			*out_red;
	int				cmd_iteration;
	int				cmd_nbr;
	char			*type[50];
	char			*file[50];
	int				fd_out;
	int				fd_in;
	char			**environ;
	char			**args_execve;
	char			*findhome;
	char			**split;
	char			*error;
	int				len;
	char			**new;
	char			**myenvp;
	int				envlen;
	int				there_is_pipe;
	int				fd[2];
	char			**envsplited;
	char			**envvariables;
	int				envvarpos;
}					t_cmdl;

int					ft_is_alpha(char c);
char				*rm_spaces(char *s);
int					check_valid(char *s);
// size_t		ft_strlen(char *s);
int					check_err_pipe(char *s);
// char	*ft_substr(char *s, unsigned int start, size_t len);
// char	*ft_strtrim(char *s1, char *set);
// size_t	ft_strlcpy(char *dst, char *src, size_t size);
int					ft_isspace(int c);
t_token				*ft_token(t_token *token, t_data *data, char *s);
// char	**ft_split(char *s, char c);
// int	ft_strcmp(char *s1, char *s2);
int					ft_check_syntax(char *s);
// void    make_cmd_perfect(t_data *data, char *s);
int					ft_isalnum(int c);
char				*ft_strcat(char *dest, char *src);
int					is_special(char c);
void				remove_quotes(t_token *token);
void				print_token(t_token *token);
void				list_files(t_token *token);

#endif

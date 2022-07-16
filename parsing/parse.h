/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarim <mkarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:56:03 by mkarim            #+#    #+#             */
/*   Updated: 2022/07/16 19:11:49 by mkarim           ###   ########.fr       */
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

typedef struct s_data
{
	char			*cmd_line;
	int				side;
	char			**cmd_sides;
	int				error;
}					t_data;

typedef struct s_token
{
	int				type;
	char			*value;
	int				sgl_qt;
	int				args_num;
	int				redi;
	int				files;
	int				count_cmd;
	struct s_token	*next;
}					t_token;

typedef struct s_files
{
	int				type;
	char			*name;
	struct s_files	*next;
}					t_files;

void				ft_putstr(char *s);
void				ft_putendl(char *s);
typedef struct s_cmd
{
	char			**cmd;
	int				cmdnbr;
	char			**f_name;
	int				*f_type;
	int				fd_out;
	int				fd_in;
	char			*delimiter;
	char			*findhome;
	int				cmd_iteration;
	char			**new;
	char			*error;
	int				count_args;
	int				envvarpos;
	int				pi[2];
	char			**splited;
	int				t;
	char			**exportnew;

	struct s_cmd	*next;
}					t_cmd;

int					ft_is_alpha(char c);
char				*rm_spaces(char *s);
int					check_valid(char *s);
int					check_err_pipe(char *s);
int					ft_isspace(int c);
t_token				*ft_token(t_token *token, t_data *data, char *s);
int					ft_check_syntax(t_data *data, char *s);
int					ft_isalnum(int c);
char				*ft_strcat(char *dest, char *src);
int					is_special(char c);
void				remove_quotes(t_token *token);
void				print_token(t_token *token);
void				list_files(t_token *token);
void				num_of_rd(t_token *token, t_cmd *cmd);
void				incr_quotes(char c, int *a, int *b);
void				print_token(t_token *token);

/* ----- START SYNTAX ERROR FUNCTIONS ----- */
int					check_pipes(char *s);
int					check_quotes(char *s);
int					is_special(char c);
int					ft_isspace(int c);
int					consec_red1(char *s);
int					consec_red2(char *s);
int					consec_redout(char *s);
int					consec_redin(char *s);
int					check_parent(char *s);
int					check_red(char *s);
void				red(void);
void				reset(void);
/* ----- END SYNTAX ERROR FUNCTIONS ----- */
t_cmd				*node_per_cmd(t_token *token);
char				*before_dol(char *str);
char				*rm_first_char(char *str);
int					dolar_exist(char *s);
char				*rest_cmp(char *str, int len);
void				mark_cmd(t_token *tok);
void				add_back_cmd(t_cmd **cmd, char **args, int *file_type,
						char **file_name);
t_cmd				*new_node_cmd(char **args, int *file_type,
						char **file_name);
char				*rest_from_index(char *str, int ind);
char				*before_index(char *str, int ind);
void				exp_exit_status(char **str);
void				ft_num_cmd_side(t_data *data, char *s);
int					ft_token_type(char *value);
void				add_file_type(t_token *token);
t_token				*ft_new_node(char *value);
void				ft_add_back(t_token **token, char *value);

#endif

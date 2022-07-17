/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:10:47 by atabiti           #+#    #+#             */
/*   Updated: 2022/07/17 12:50:27 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include "./parsing/parse.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# define SUCCESSFUL 0
# define UNSUCCESSFUL 1

typedef struct t_list
{
	char	*content;
	void	*next;
}			t_list;
int			g_exit_status;

typedef struct s_env
{
	char	*name;
	char	*value;
}			t_env;
t_env		*new_node(char *name, char *value);

t_lis		*copyenv(t_lis *env_clone, char **env);
void		free_environ(t_lis *head);

char	**convertlisttoarray(t_lis *envp);
int	ft_export_no_equal(t_lis *envp,
						t_cmd *cmd,
						int i);
int			pass_to_exec(t_lis *envp, t_cmd *cmds);
void	signal_init(void);
void	voidthem(int argc, char **argv);
void	checkline(t_data data);
//input
void		handler(int sig);
int			prompt_and_parse(char **upstream, char **downstream, char *line);
void		rl_replace_line(const char *text, int clear_undo);
void		rl_clear_history(void);
// Builtin Commands
int			ft_pwd(int fd_out);
int			builtcheck_1(t_cmd *cmd, t_lis *envp);
int			ftexit(t_cmd *cmd, t_lis *envp);
int			builtcheck(t_lis *envp, t_cmd *cmds);
int			ftcd(t_cmd *cmd, t_lis *envp);
int			ft_export_1(t_lis *envp, char **joined);
int			ft_env(t_lis *envp, t_cmd *cmd);
int			ft_echo(t_cmd *cmds, int fd);
int			ft_is_built_in(t_lis *envp, t_cmd *cmds);
int			ft_unset(t_lis *envp, t_cmd *list, int arg);

int			ft_export(t_lis *envp, t_cmd *cmd, int i);
//execve
int			is_builtin(t_cmd *cmds);
int			one_cmd(t_lis *envp, t_cmd *cmds);
char		*ft_itoa(int n);
int			ft_split_env(t_lis *envp, char **env);
int			set_rd(t_cmd *list);
int			builtcheck_next(t_cmd *cmd, t_lis *envp);
int			ft_bin_usr_sbin(t_cmd *cmd, t_lis *envp);
int	ft_search_for_path(t_cmd *list,
						t_lis *envp);
void		ftcheck_nopath(t_cmd *list, t_lis *envp);
void		looping_through_split_path(t_cmd *list, char *bin, char *last,
				t_lis *envp);
int	ft_check_programs(t_cmd *list,
						t_lis *envp);
/// redirections I/O
int			redirections(t_cmd *list);
int			heredoc_exec(t_cmd *list);

//env
// LIBFT
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *s1);
void		*ft_memmove(void *s1, void *s2, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		*ft_memmove(void *s1, void *s2, size_t len);
int			ft_search(char *s, char *c, int lenght);
// output libft
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
// pipes
int			ft_pipe(t_cmd *list, t_lis *envp, int id, int fdin);
// signals
void		handler(int sig);
// init data
int			ft_init(t_cmd *cmds);
//export tools
char		*join_name_and_value(t_lis *envp);
char		*ft_sort_env(t_lis *envp);
int			check_name_is_valid(char *split, int i, t_cmd *cmd);
int			ft_equal_sign(t_cmd *list, int arg);
char		*extractname(t_cmd *cmd, int i);
void		modify(t_lis *envp, t_cmd *cmd, int i, char *name);
char		*extractvalue(t_cmd *cmd, int i);
int			valid_identifier(t_lis *envp, t_cmd *cmd, int i);

//free
void		freeit(char *name, char *value);
int			ft_is_alpha_mod(char c);
//tmp
void		print_cmd(t_cmd *cmd);
//heredoc
int			heredoc_exec_part1(t_cmd *list, int i, int id, int len);
char		*heredoc_reader(t_cmd *list, char *line);
int			heredoc_wait(int id);
void		heredoc_write_fd(char *line, int fd);
void		heredoc_exec_clean(char *line, int fd);
void		handler_in_heredoc(int sig);
int			heredoc_exec(t_cmd *list);
void		exp_change_value(t_lis *envp, t_token *token);
char				*ft_ass_exp(char **tok_val, char *sp, t_env *env);

#endif

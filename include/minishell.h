/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:36:52 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/25 17:55:06 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
// limits.h PATH_MAX
# include <stdbool.h>
// # include <readline/rltypedefs.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stddef.h>
# include <ctype.h>
# include <signal.h>
# include "libft.h"

# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '\"'
# define ERROR_TOKENIZE 258
# define ERROR_PARSE 258
# define ERROR_OPEN_REDIR 1
# define STDOUT_FILENO 1
# define STDIN_FILENO 0
# define CHILD_PID 0
# define NOT_CONTROL_CHARS 0
# define SHELL_PROMPT "\x1b[96mminishell\x1b[0m$ "
# define NEW_LINE "\n"
# define ERROR_PREFIX "minishell: "
# define FATAL_ERROR "Fatal Error: "
# define SYNTAX_ERROR "syntax error near "
# define TODO_ERROR "TODO: "
# define ASSERT_ERROR "Assert Error: "

extern int	last_status;
extern bool	syntax_error;
extern bool	readline_interrupted;
extern volatile sig_atomic_t	sig;
extern int	_rl_echo_control_chars;

typedef enum e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
}	t_token_kind;

typedef struct s_token
{
	char		*word;
	t_token_kind	kind;
	struct s_token	*next;
}	t_token;

typedef enum e_node_kind
{
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
	ND_REDIR_IN,
	ND_REDIR_APPEND,
	ND_REDIR_HEREDOC,
	ND_PIPELINE,
}	t_node_kind;

typedef struct s_node
{
	t_node_kind		kind;
	struct s_node	*next;
	// CMD
	t_token			*args;
	// REDIR
	struct s_node	*redirects;
	int				targetfd;
	t_token			*filename;
	t_token			*delimiter;
	int				filefd;
	int				stashed_targetfd;
	bool			is_delimiter_quote;
	// PINELINE
	struct s_node	*command;
	int				inpipe[2];
	int				outpipe[2];
}	t_node;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

void	print_envp(char **envp);
void	print_token(t_token *token);
// free
void	free_node(t_node *node);
void	free_argv(char **argv);
// error
void	fatal_error(const char *str);
void	assert_error(const char *str);
void	todo(const char *msg);
void	err_exit(const char *location, const char *msg, int status);
void	xperror(const char *location);
void	builtin_error(char *func, char *name, char *err_message);
// exec
int		exec(t_node *node, t_env **env);
// tokenizer
t_token	*tokenize(char	*line);
void	free_token(t_token *token);
void	free_argv(char **argv);
char	**add_token_to_argv(t_token *tok);
void	tokenize_error(const char *location, char **rest, char *line);
t_token	*create_new_token_list(char *word, t_token_kind kind);
bool	is_word(char *line);
t_token	*add_word_to_list(char **rest_line, char *line);
bool	is_operator(char *line);
t_token	*add_operator_to_list(char **rest_line, char *line);
bool	is_blank(char c);
void	skip_blank(char **skip_line, char *line);
// expansion
void	expand(t_node *node, t_env **env);
void	remove_quote(t_node *node);
void	append_char(char **s, char c);
void	expand_variable(t_node *node, t_env **env);
char	*expand_heredoc_line(char *line, t_env **env);
bool	is_variable(char *s);
void	expand_parameter_str(char **new_word, char **rest, char *current_word);
void	expand_variable_str(char **new_word, char **rest, char *current_word, t_env **env);
bool	is_special_parametar(char *str);
bool	is_alpha_num_under(char c);
bool	is_alpha_under(char c);
bool	is_expand_variable(char *s);
// parser
t_node	*parse(t_token *token);
// redirection
int		open_redirect_file(t_node *redirect, t_env **env);
void	do_redirect(t_node *redirect);
void	reset_redirect(t_node *redirect);
// pipeline
void	prepare_pipe(t_node *node);
void	prepare_pipe_child(t_node *node);
void	prepare_pipe_parent(t_node *node);
// signal
void	set_signal(void);
void	reset_signal_to_default(void);
// builtin
bool	is_builtin(t_node *node);
int	exec_builtin_exit(char **argv);
int	exec_builtin_echo(char **argv);
int	count_argc(char **argv);
int	exec_builtin_pwd(char **argv, t_env **env);
int	exec_builtin_cd(char **argv, t_env **env);
int		exec_builtin_cmd(t_node *node, t_env **env);
int		exec_builtin_exit(char **argv);
int		exec_builtin_echo(char **argv);
int		count_argc(char **argv);
int		exec_builtin_export(char **argv, t_env **env);
int		get_cwd(t_env **env);
int	exec_builtin_unset(char **argv, t_env **env);
int	exec_builtin_env(t_env **env);
// environ
void	print_env(t_env *env);
t_env	*init_env_list(char **envp);
void	add_key_value_to_env(t_env **env, char *key, char *value);
int	set_env_list(t_env **env, char *str);
char	*ft_getenv(char *path_key, t_env **env);
t_env	*create_new_env_list(char *key, char *value);
bool	is_variable(char *str);
void	update_value_to_env(t_env **env, char *key, char *value);
void	add_key_value_to_env(t_env **env, char *key, char *value);
int	unset_env_list(t_env **env, char *str);

#endif

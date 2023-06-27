/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:36:52 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/27 17:06:33 by yuohno           ###   ########.fr       */
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
# include <fcntl.h>
# include "libft.h"

# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '\"'
# define ERROR_TOKENIZE 258
# define ERROR_PARSE 258
# define CHILD_PID 0
// # define STDOUT_FILENO 1
// # define STDIN_FILENO 0
# define SHELL_PROMPT "\x1b[96mminishell\x1b[0m$ "
# define NEW_LINE "\n"
# define ERROR_PREFIX "minishell: "
# define FATAL_ERROR "Fatal Error: "
# define SYNTAX_ERROR "syntax error near "
# define COMMAND_NOT_FOUND ": command not found"
# define IS_DIR ": is a directory"
# define PER_DENY ": permission deny"
# define ERROR_PARSE_MSG "unexpected token "
# define ERROR_PARSE_LOCATION "`simple_command function'"
# define ERROR_LEXER_MSG "unexpected characters "
# define ERROR_LEXER_LOCATION "`unexpected token'"
# define ERROR_SINGLE "Unclosed sigle quote"
# define ERROR_DOUBLE "Unclosed double quote"

extern struct s_data	g_data;

typedef struct s_data
{
	int						last_status;
	bool					readline_interrupted;
	volatile sig_atomic_t	sig;
}	t_data;

typedef enum e_token_kind
{
	TK_WORD,
	TK_OP,
	TK_EOF,
}	t_token_kind;

typedef struct s_token
{
	char			*word;
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
	t_token			*args;
	struct s_node	*redirects;
	int				std_fd;
	t_token			*filename;
	t_token			*delimiter;
	int				filefd;
	int				stashed_std_fd;
	bool			is_delimiter_quote;
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

// free
void	free_node(t_node *node);
void	free_argv(char **argv);
// error
void	fatal_error(const char *str);
void	err_exit(const char *location, const char *msg, int status);
void	builtin_error(char *func, char *name, char *err_message);
void	parse_error(const char *location, t_token **rest,
			t_token *token, int *syntax_error);
// exec
void	exec(t_node *node, t_env **env);
int		wait_pipeline(pid_t last_child_pid);
char	*check_cmd_path(const char *filename, t_env **env);
bool	check_is_filename(const char *path, const char *filename);
void	exec_simple_cmd(t_node *node, t_env **env);
// tokenizer
t_token	*tokenize(char	*line, int *syntax_error);
void	free_token(t_token *token);
void	free_argv(char **argv);
char	**add_token_to_argv(t_token *tok);
void	tokenize_error(const char *location, char **rest,
			char *line, int *syntax_error);
t_token	*create_new_token_list(char *word, t_token_kind kind);
bool	is_word(char *line);
t_token	*add_word_to_list(char **rest_line, char *line, int *syntax_error);
bool	is_operator(char *line);
t_token	*add_operator_to_list(char **rest_line, char *line);
bool	is_blank(char c);
void	skip_blank(char **skip_line, char *line);
// expansion
void	expand(t_node *node, t_env **env);
void	remove_quote(t_node *node);
void	append_char(char **s, char c);
void	append_double_quote(char **new_word, char **rest,
			char *current_word, t_env **env);
void	append_single_quote(char **new_word, char **rest, char *current_word);
void	expand_variable(t_node *node, t_env **env);
char	*expand_heredoc_line(char *line, t_env **env);
bool	is_variable(char *s);
void	expand_parameter_str(char **new_word, char **rest, char *current_word);
void	expand_variable_str(char **new_word, char **rest,
			char *current_word, t_env **env);
bool	is_special_parametar(char *str);
bool	is_metacharacter(char c);
bool	is_alpha_num_under(char c);
bool	is_alpha_under(char c);
bool	is_expand_variable(char *s);
bool	is_quote_after_dollar(char *str);
void	expand_variable_token(t_token *token, t_env **env);
void	remove_quote_token(t_token *token);
void	remove_single_quote(char **dst, char **rest, char *p);
void	remove_double_quote(char **dst, char **rest, char *p);
// parser
t_node	*parse(t_token *token, int *syntax_error);
t_node	*pipeline(t_token **rest, t_token *token, int *syntax_error);
t_node	*simple_command(t_token **rest, t_token *token, int *syntax_error);
t_node	*create_new_redirect_heredoc(t_token **rest, t_token *token);
t_node	*create_new_redirect_append(t_token **rest, t_token *token);
t_node	*create_new_redirect_in(t_token **rest, t_token *token);
t_node	*create_new_redirect_out(t_token **rest, t_token *token);
void	add_token_to_node(t_token **node_token, t_token *new_token);
void	add_operator_to_node(t_node **node, t_node *new_node);
t_token	*tokendup(t_token *token);
t_node	*create_new_node_list(t_node_kind kind);
bool	check_operator(t_token *token, char *op);
// redirection
int		open_redirect_file(t_node *redirect, t_env **env);
void	do_redirect(t_node *redirect);
bool	is_redirect(t_node *redirect);
void	reset_redirect(t_node *redirect);
int		read_heredoc(const char *delimiter,
			bool is_delimiter_quote, t_env **env);
int		stashfd(int fd);
// pipeline
void	prepare_pipe(t_node *node);
void	prepare_pipe_child(t_node *node);
void	prepare_pipe_parent(t_node *node);
// signal
void	set_signal(void);
void	reset_signal_to_default(void);
// builtin
bool	is_builtin(t_node *node);
int		exec_builtin_exit(char **argv);
int		exec_builtin_echo(char **argv);
int		count_argc(char **argv);
int		exec_builtin_pwd(char **argv, t_env **env);
int		exec_builtin_cd(char **argv, t_env **env);
int		exec_builtin_cmd(t_node *node, t_env **env);
int		exec_builtin_exit(char **argv);
int		exec_builtin_echo(char **argv);
int		count_argc(char **argv);
int		exec_builtin_export(char **argv, t_env **env);
int		get_cwd(t_env **env);
int		exec_builtin_unset(char **argv, t_env **env);
int		exec_builtin_env(t_env **env);
// environ
void	print_env(t_env *env);
t_env	*init_env_list(char **envp);
void	add_key_value_to_env(t_env **env, char *key, char *value);
int		set_env_list(t_env **env, char *str);
char	*ft_getenv(char *path_key, t_env **env);
t_env	*create_new_env_list(char *key, char *value);
bool	is_variable(char *str);
void	update_value_to_env(t_env **env, char *key, char *value);
void	add_key_value_to_env(t_env **env, char *key, char *value);
int		unset_env_list(t_env **env, char *str);
// debug_print
// void	print_envp(char **envp);
// void	print_token(t_token *token);
// void	print_argv(char **str);

#endif

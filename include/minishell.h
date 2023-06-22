/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:36:52 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/22 19:02:21 by rnaka            ###   ########.fr       */
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
# include <readline/rltypedefs.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <stddef.h>
# include <ctype.h>
# include <signal.h>

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

typedef struct s_path
{
	char	*pwd;
	char	*old;
}	t_path;


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
// exec
int	exec(t_node *node);
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
void	expand(t_node *node);
void	remove_quote(t_node *node);
void	append_char(char **s, char c);
void	expand_variable(t_node *node);
char	*expand_heredoc_line(char *line);
bool	is_variable(char *s);
void	expand_parameter_str(char **new_word, char **rest, char *current_word);
void	expand_variable_str(char **new_word, char **rest, char *current_word);
bool	is_special_parametar(char *str);
// parser
t_node	*parse(t_token *token);
// redirection
int		open_redirect_file(t_node *redirect);
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
int	exec_builtin_cmd(t_node *node);
int	exec_builtin_exit(char **argv);
int	exec_builtin_echo(char **argv);
int	count_argc(char **argv);
int	exec_builtin_pwd(char **argv, t_path *path);
int	exec_builtin_cd(char **argv, t_path *path);

#endif

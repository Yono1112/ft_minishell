/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:36:52 by yumaohno          #+#    #+#             */
/*   Updated: 2023/05/08 12:28:53 by yuohno           ###   ########.fr       */
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
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <stddef.h>

# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '\"'
# define ERROR_TOKENIZE 258
# define ERROR_OPEN_REDIR 1

extern bool	syntax_error;

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
}	t_node_kind;

typedef struct s_node
{
	t_node_kind		kind;
	struct s_node	*next;
	// CMD
	t_token			*args;
	struct s_node	*redirects;
	// REDIR
	int				targetfd;
	t_token			*filename;
	int				filefd;
	int				stashed_targetfd;
}	t_node;

// error
void	fatal_error(const char *str);
void	assert_error(const char *str);
void	todo(const char *msg);
void	err_exit(const char *location, const char *msg, int status);
void	xperror(const char *location);
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
// parser
t_node	*parse(t_token *token);
void	free_node(t_node *node);
// redirection
int		open_redirect_file(t_node *redirect);
void	do_redirect(t_node *redirect);
void	reset_redirect(t_node *redirect);

#endif
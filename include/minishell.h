/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:36:52 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/30 14:40:14 by yumaohno         ###   ########.fr       */
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

# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '\"'

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

// tokenizer
t_token	*tokenize(char	*line);
void	free_token(t_token *token);
void	free_argv(char **argv);
char	**token_list_to_argv(t_token *tok);
void	fatal_error(const char *str);
void	assert_error(const char *str);
void	todo(const char *msg);
t_token	*create_new_token_list(char *word, t_token_kind kind);
bool	is_word(char *line);
t_token	*add_word_to_list(char **rest_line, char *line);
bool	is_operator(char *line);
t_token	*add_operator_to_list(char **rest_line, char *line);
bool	is_blank(char c);
void	skip_blank(char **skip_line, char *line);
void	expand(t_token *token);

#endif
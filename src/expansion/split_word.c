/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:11:59 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 00:15:34 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_defalut_ifs(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

bool	is_custom_ifs(char c, t_env **env)
{
	char	*ifs_word;

	// printf("start is_custom_ifs\n");
	// printf("c:%c\n", c);
	if (c != '\0')
	{
		ifs_word = ft_getenv("IFS", env);
		// printf("ifs_word:%s\n", ifs_word);
		if (ifs_word == NULL)
			return (false);
		else
		{
			// printf("ifs_word is not NULL\n");
			if (strchr(ifs_word, c) != NULL) 
			{
				// printf("true\n");
				return (true);
			}
		}
	}
	// printf("false\n");
	return (false);
}

void	skip_defalut_ifs(char **rest, char *current_word)
{
	// for(int i = 0; current_word[i]; i++)
	// 	printf("current_word[%d]:%c", i, current_word[i]);
	// printf("start skip_defalut_ifs\n");
	while (*current_word)
	{
		if (!is_defalut_ifs(*current_word))
			break ;
		// printf("current_word++\n");
		current_word++;
	}
	// printf("current_word:%c\n", *current_word);
	*rest = current_word;
	// printf("finish skip_defalut_ifs\n");
}

void	skip_custom_ifs(char **new_word, char **rest, char *current_word, t_env **env)
{
	// for(int i = 0; current_word[i]; i++)
	// 	printf("current_word[%d]:%c", i, current_word[i]);
	size_t	i;
	size_t	j;

	(void)new_word;
	(void)env;
	i = 0;
	j = 1;
	// printf("start skip_custom_ifs\n");
	while (current_word[i])
	{
		// printf("current_word[%zu]:%c\n", i, current_word[i]);
		// printf("current_word[%zu]:%c\n", j, current_word[j]);
		if (!is_defalut_ifs(current_word[i]))
			break ;
		// else
		// 	printf("false skip_custom_ifs\n");
		// current_word++;
		// printf("current_word++\n");
		i++;
		j++;
	}
	j = i - 1;
	// if (current_word[i] == '\0' && is_defalut_ifs(current_word[j]))
	// {
	// 	// printf("last current_word and true is_defalut_ifs\n");
	// 	append_char(new_word, ' ');
	// }
	// printf("current_word:%c\n", *current_word);
	*rest = &current_word[i];
	// printf("finishe skip_custom_ifs\n");
	// // for(int i = 0; current_word[i]; i++)
	// // 	printf("current_word[%d]:%c", i, current_word[i]);
	// size_t	i;
	// size_t	j;

	// i = 0;
	// j = 1;
	// // printf("start skip_custom_ifs\n");
	// while (current_word[i])
	// {
	// 	// printf("current_word[%zu]:%c\n", i, current_word[i]);
	// 	// printf("current_word[%zu]:%c\n", j, current_word[j]);
	// 	if (!is_custom_ifs(current_word[i], env))
	// 		break ;
	// 	if (is_custom_ifs(current_word[i], env) && current_word[j] && !is_custom_ifs(current_word[j], env) && !is_defalut_ifs(current_word[j]))
	// 	{
	// 		// printf("true skip_custom_ifs\n");
	// 		// printf("add space append_char999999999999999999999999999999999999999999999\n");
	// 		append_char(new_word, '0');
	// 	}
	// 	// else
	// 	// 	printf("false skip_custom_ifs\n");
	// 	// current_word++;
	// 	// printf("current_word++\n");
	// 	i++;
	// 	j++;
	// }
	// j = i - 1;
	// if (current_word[i] == '\0' && is_defalut_ifs(current_word[j]))
	// {
	// 	// printf("last current_word and true is_defalut_ifs\n");
	// 	append_char(new_word, ' ');
	// }
	// // printf("current_word:%c\n", *current_word);
	// *rest = &current_word[i];
	// // printf("finishe skip_custom_ifs\n");
}

void	split_token_with_ifs(char **new_word, t_token *token, t_token **rest_token)
{
	t_token *new_token;

	// printf("start split_token_with_ifs\n");
	token->word = *new_word;
	// printf("token->word:%s===\n", token->word);
	*new_word = calloc(1, sizeof(char));
	new_token = create_new_token_list(NULL, TK_WORD);
	new_token->next = token->next;
	token->next = new_token;
	*rest_token = token->next;
}

void	split_word_token(t_token *token, t_env **env)
{
	char	*new_word;
	char	*current_word;
	char	*free_word;

	// printf("start split_word_token\n");
	while (token != NULL)
	{
		free_word = token->word;
		if (token->is_expanded)
		{
			// printf("true token->is_expanded\n");
			printf("token->word:%s=\n", token->word);
			// exit(0);
			current_word = token->word;
			new_word = calloc(1, sizeof(char));
			if (new_word == NULL)
				fatal_error("calloc");
			// if (is_custom_ifs(*current_word, env))
			// 	skip_custom_ifs(&new_word, &current_word, current_word, env);
			while (*current_word)
			{
				// printf("*current_word:%c\n", *current_word);
				if (is_defalut_ifs(*current_word) && ft_getenv("IFS", env) == NULL)
				{
					// printf("true is_defalut_ifs\n");
					skip_defalut_ifs(&current_word, current_word);
					if (*current_word != '\0')
						split_token_with_ifs(&new_word, token, &token);
				}
				else if (*current_word == SINGLE_QUOTE_CHAR)
					append_single_quote(&new_word, &current_word, current_word);
				else if (*current_word == DOUBLE_QUOTE_CHAR)
					append_double_quote(&new_word, &current_word, current_word, env);
				else
					append_char(&new_word, *current_word++);
				// printf("===============================================\n");
				// sleep(1);
			}
			free(free_word);
			token->word = new_word;
			// printf("after token->word:%s=\n", token->word);
		}
		// else
		//	printf("false token->is_expanded\n");
		token = token->next;
		// printf("token = token->next\n");
	}
	// char	*new_word;
	// char	*current_word;
	// char	*free_word;

	// // printf("start split_word_token\n");
	// while (token != NULL)
	// {
	// 	free_word = token->word;
	// 	if (token->is_expanded)
	// 	{
	// 		// printf("true token->is_expanded\n");
	// 		// printf("token->word:%s\n", token->word);
	// 		// exit(0);
	// 		current_word = token->word;
	// 		new_word = calloc(1, sizeof(char));
	// 		if (new_word == NULL)
	// 			fatal_error("calloc");
	// 		if (is_custom_ifs(*current_word, env))
	// 			skip_custom_ifs(&new_word, &current_word, current_word, env);
	// 		while (*current_word)
	// 		{
	// 			// printf("*current_word:%c\n", *current_word);
	// 			if (is_custom_ifs(*current_word, env))
	// 			{
	// 				// printf("true is_custom_ifs\n");
	// 				skip_custom_ifs(&new_word, &current_word, current_word, env);
	// 				split_token_with_ifs(&new_word, token, &token);
	// 			}
	// 			else if (is_defalut_ifs(*current_word) && ft_getenv("IFS", env) == NULL)
	// 			{
	// 				// printf("true is_defalut_ifs\n");
	// 				skip_defalut_ifs(&current_word, current_word);
	// 				split_token_with_ifs(&new_word, token, &token);
	// 			}
	// 			else if (*current_word == SINGLE_QUOTE_CHAR)
	// 				append_single_quote(&new_word, &current_word, current_word);
	// 			else if (*current_word == DOUBLE_QUOTE_CHAR)
	// 				append_double_quote(&new_word, &current_word, current_word, env);
	// 			else
	// 				append_char(&new_word, *current_word++);
	// 			// printf("===============================================\n");
	// 			// sleep(1);
	// 		}
	// 		free(free_word);
	// 		token->word = new_word;
	// 		// printf("after token->word:%s\n", token->word);
	// 	}
	// 	// else
	// 	//	printf("false token->is_expanded\n");
	// 	token = token->next;
	// 	// printf("token = token->next\n");
	// }
	// print_token(token);
}

void	split_word(t_node *node, t_env **env)
{
	// printf("start split_word\n");
	while (node != NULL)
	{
		if (node->command != NULL)
		{
			split_word_token(node->command->args, env);
			// print_token(node->command->args);
		}
		if (node->command->redirects != NULL)
			split_word_token(node->command->redirects->filename, env);
		node = node->next;
	}
}

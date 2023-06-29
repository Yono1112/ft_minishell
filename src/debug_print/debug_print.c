/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:00:47 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 11:00:54 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_argv(char **str)
// {
// 	int	i = 0;

// 	while (str[i])
// 	{
// 		printf("str[%d]:%s\n", i, str[i]);
// 		i++;
// 	}
// }

// void	print_token(t_token *token)
// {
// 	while (token && token->kind != TK_EOF)
// 	{
// 		printf("token_word: %s\n", token->word);
// 		token = token->next;
// 	}
// }

// void	print_env(t_env *env)
// {
// 	printf("start print_env\n");
// 	printf("=======================================================\n");
// 	while (env)
// 	{
// 		printf("env->key:%s, env->value:%s\n", env->key, env->value);
// 		env = env->next;
// 	}
// }

// void	print_node(t_node *node)
// {
// 	if (node->command->args)
// 	{
// 		printf("node->command->args\n");
// 		print_token(node->command->args);
// 	}
// 	if (node->command->redirects)
// 	{
// 		printf("node->command->redirects\n");
// 		print_token(node->command->args);
// 		print_token(node->command->redirects->filename);
// 		print_token(node->command->redirects->delimiter);
// 	}
// 	if (node->next)
// 		print_node(node->next);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_filename.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 00:37:44 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 17:39:58 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_is_filename(const char *path, const char *filename)
{
	struct stat	sb;

	if (!ft_strcmp(filename, ":"))
		return (false);
	if (path == NULL)
		return (false);
	else if (!ft_strcmp(filename, ""))
		return (false);
	else if (!ft_strcmp(filename, ".."))
		return (false);
	else if (access(path, F_OK) < 0)
		return (false);
	if (access(path, X_OK) < 0)
		err_exit(path, PER_DENY, 126);
	if (stat(path, &sb) < 0)
		fatal_error("fstat");
	if (!S_ISREG(sb.st_mode) && S_ISDIR(sb.st_mode))
		err_exit(filename, IS_DIR, 126);
	return (true);
}

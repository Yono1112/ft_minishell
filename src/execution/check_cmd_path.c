/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 00:36:24 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 00:36:42 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	make_pathlen(char **end,
							char *path, char **value)
{
	size_t	path_len;

	*end = ft_strchr(*value, ':');
	if (*end)
		path_len = (size_t)(*end - *value);
	else
		path_len = ft_strlen(*value);
	if (path_len >= PATH_MAX)
		return (1);
	ft_memcpy(path, *value, path_len);
	path[path_len] = '\0';
	ft_strncat(path, "/", PATH_MAX - ft_strlen(path) - 1);
	return (0);
}

char	*check_cmd_path(const char *filename, t_env **env)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;
	char	*dup;

	value = ft_getenv("PATH", env);
	if (!value)
		return (NULL);
	while (*value)
	{
		if (make_pathlen(&end, path, &value))
			return (NULL);
		ft_strncat(path, filename, PATH_MAX - ft_strlen(path) - 1);
		if (access(path, X_OK) == 0)
		{
			dup = ft_strdup(path);
			if (!dup)
				return (NULL);
			return (dup);
		}
		if (end == NULL)
			break ;
		value = end + 1;
	}
	return (NULL);
}

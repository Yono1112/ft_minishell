/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stashfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 01:16:15 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 01:24:42 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_fcntl(int fd)
{
	int		stashed_fd;
	int		target_fd;
	struct stat	stat;

	target_fd = 10;
	errno = 0;
	if (fd < 0)
	{
		errno = EBADF;
		return (-1);
	}
	while (!fstat(target_fd, &stat) && errno != EBADF)
		target_fd++;
	stashed_fd = dup2(fd, target_fd);
	return (stashed_fd);
}

int	stashfd(int fd)
{
	int		stashfd;

	stashfd = ft_fcntl(fd);
	if (stashfd < 0)
		fatal_error("ft_fcntl");
	if (close(fd) < 0)
		fatal_error("close");
	return (stashfd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:20:46 by rnaka             #+#    #+#             */
/*   Updated: 2023/06/25 04:08:12 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H
# include<stdlib.h>
# include<stdio.h>
# include<unistd.h>
# include<stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 25
# endif

int		ft_isalpha(int a);
int		ft_isdigit(int a);
int		ft_isalnum(int a);
int		ft_isascii(int a);
int		ft_isprint(int a);
void	*ft_memset(void *buf, int ch, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *buf1, const void *buf2, size_t n);
void	*ft_memmove(void *buf1, const void *buf2, size_t n);
size_t	ft_strlen(const char *a);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *buf, int ch, size_t n);
int		ft_memcmp(const void *buf1, const void *buf2, size_t count);
char	*ft_strnstr(const char	*b, const char *l, size_t n);
int		ft_atoi(const char *s);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const*s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_printf(const char *fmt, ...);
int		ft_putchar(char c);
int		ft_putstr(const char *str);
int		ft_putpointer(unsigned long long point);
int		ft_putnbrbase(long int n, int base, char c, int count);
int		ft_putulong(unsigned int n, int base, char c, int count);
char    *ft_strndup(const char *s, size_t n);
int	ft_isspace(char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strncat(char *dst, const char *src, size_t len);
#endif

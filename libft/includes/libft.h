/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:23:28 by makurek           #+#    #+#             */
/*   Updated: 2025/09/26 16:43:59 by makurek          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
//ft_printf
# include <stdarg.h>
# include <stdio.h>
# include <stdint.h>

//str
int		ft_atoi(const char *str);
int		ft_isalnum(const int c);
int		ft_isalpha(const int c);
int		ft_isascii(const int c);
int		ft_isdigit(const int c);
int		ft_isprint(const int c);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(const char *s1);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *dst, const char *src, size_t n);
char    *ft_strndup(const char *src, size_t n);
size_t  ft_strnlen(const char *s, size_t maxlen);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
int		ft_strspn(const char *s, const char *accept);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_strspn(const char *s, const char *accept);
int		is_sign(const char c);
int		is_space(const char c);
char	*skip(const char *str, int is_something(const char));

//ft_printf
int		ft_printf(const char *str, ...);
int		ft_write_char(const char c);
void	ft_write_str(char *str, int *out);
void	ft_write_uint(uint32_t n, int *out);
void	ft_write_integer(int i, int	*out);
void	ft_write_hex_low(uint32_t nbr, int *out);
void	ft_write_hex_high(uint32_t nbr, int *out);
void	ft_write_ptr(void *ptr, int *out);
void	ft_check_error(int res, int *out);

//print
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);

//memory
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
//get_next_line?

//array
int		arraylen(void **array);
void	*free_array(char **array);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:18:58 by makurek           #+#    #+#             */
/*   Updated: 2024/12/20 16:49:15 by makurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
//# include <stdio.h>
//# include <fcntl.h>

# ifndef MAX_FD
#  define MAX_FD 4096
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

typedef struct s_struct
{
	char	buffer[BUFFER_SIZE + 1];
	char	*current;
	int		bytes_read;
}	t_buffer;

char	*get_next_line(int fd, int *err);

#endif

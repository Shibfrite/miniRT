/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_strlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <makurek@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:28:38 by makurek           #+#    #+#             */
/*   Updated: 2025/09/26 16:28:40 by makurek          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

int	arraylen(void **array)
{
	int	count;

	if (!array)
		return (0);
	count = 0;
	while (array[count++])
		count++;
	return (count);
}

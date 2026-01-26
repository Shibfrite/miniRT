/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strspn.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <makurek@student.42lausanne.ch>       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/01/26 15:50:13 by makurek        #+#    #+#                */
/*   Updated: 2026/01/26 15:50:15 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

int	ft_strspn(const char *s, const char *accept)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	while (s[i])
	{
		j = 0;
		found = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
			{
				found = 1;
				break ;
			}
			j++;
		}
		if (!found)
			break ;
		i++;
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 10:32:29 by lbartels      #+#    #+#                 */
/*   Updated: 2023/10/26 19:53:10 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	while (n > 0)
	{
		((char *)s)[n - 1] = c;
		n--;
	}
	return (s);
}

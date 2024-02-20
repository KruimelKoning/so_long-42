/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 17:25:15 by lbartels      #+#    #+#                 */
/*   Updated: 2023/10/30 15:14:03 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_string(long n, int len, char *str)
{
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n != 0)
	{
		str[--len] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}

static int	ft_count_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_count_len(n);
	str = (char *)ft_calloc(sizeof(char), len + 1);
	if (!str)
		return (NULL);
	str = ft_string(n, len, str);
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 14:07:33 by lbartels      #+#    #+#                 */
/*   Updated: 2023/10/09 14:07:33 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_len(int start, int end)
{
	if (end - start < 0)
		return (0);
	return (end - start);
}

static int	check_set(char const s, char const *set)
{
	while (*set != '\0')
	{
		if (s == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	char	*ptr;
	int		i;
	int		start;
	int		end;

	start = 0;
	while (check_set(s[start], set) == 1)
		start++;
	end = ft_strlen((char *)s);
	if (end != 0)
		while (check_set(s[end - 1], set) == 1)
			end--;
	ptr = (char *)malloc(sizeof(char) * check_len(start, end) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (end > start)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}

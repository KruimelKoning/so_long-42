/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/16 17:04:53 by lbartels      #+#    #+#                 */
/*   Updated: 2024/02/20 14:40:22 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long.h"

char	*read_map(int fd)
{
	int		bytes_read;
	char	*buffer;
	char	*str;

	buffer = ft_calloc(2, sizeof(char));
	str = ft_calloc(2, sizeof(char));
	if (!buffer | !str)
		exit(1);
	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, buffer, 1);
		if (bytes_read == -1)
		{
			free(str);
			free(buffer);
			exit(1);
		}
		if (bytes_read)
			str = str_join(str, buffer);
	}
	free(buffer);
	return (str);
}

bool	quick_check(char *str, char *allowed)
{
	int	i;
	int	e;
	int	p;

	i = 0;
	e = 0;
	p = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (!ft_strchr(allowed, str[i]))
			return (false);
		if (str[i] == 'E')
			e++;
		else if (str[i] == 'P')
			p++;
		else if (str[i] == '\n' && str[i + 1] == '\n')
			return (false);
		i++;
	}
	if (e != 1 || p != 1)
		return (false);
	return (true);
}

char	**make_array(int fd, char *allowed)
{
	char	**map;
	char	*str;

	str = read_map(fd);
	if (!quick_check(str, allowed))
	{
		free(str);
		ft_error(2);
	}
	map = ft_split(str, '\n');
	if (!map)
	{
		free(str);
		ft_error(3);
	}
	free(str);
	return (map);
}

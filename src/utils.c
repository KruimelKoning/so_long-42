/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/12 17:10:11 by lbartels      #+#    #+#                 */
/*   Updated: 2024/02/16 18:24:16 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long.h"

void	ft_error(char error)
{
	ft_putstr_fd(RED, 2);
	if (error == 1)
		ft_putstr_fd("invalid arguments\n", 2);
	if (error == 2)
		ft_putstr_fd("invalid map\n", 2);
	if (error == 3)
		ft_putstr_fd("error while initializing\n", 2);
	if (error == 4)
		ft_putstr_fd("error opening file\n", 2);
	ft_putstr_fd(WHITE, 2);
	exit(1);
}

char	*str_join(char *dest, char *src)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc(ft_strlen(dest) + ft_strlen(src) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (dest[i])
	{
		new_str[i] = dest[i];
		i++;
	}
	j = 0;
	while (src[j])
	{
		new_str[i + j] = src[j];
		j++;
	}
	free(dest);
	new_str[i + j] = '\0';
	return (new_str);
}

bool	flood_fill(t_vars vars, bool *empty, t_vector2 pos, t_vector2 pos2)
{
	if (pos.x == pos2.x && pos.y == pos2.y)
		return (true);
	empty[pos.x + (pos.y * vars.width)] = true;
	if (vars.map[pos.y + 1][pos.x] != '1'
		&& empty[pos.x + ((pos.y + 1) * vars.width)] == false
		&& flood_fill(vars, empty, (t_vector2){pos.x, pos.y + 1}, pos2))
		return (true);
	if (vars.map[pos.y - 1][pos.x] != '1'
		&& empty[pos.x + ((pos.y - 1) * vars.width)] == false
		&& flood_fill(vars, empty, (t_vector2){pos.x, pos.y - 1}, pos2))
		return (true);
	if (vars.map[pos.y][pos.x + 1] != '1'
		&& empty[(pos.x + 1) + (pos.y * vars.width)] == false
		&& flood_fill(vars, empty, (t_vector2){pos.x + 1, pos.y}, pos2))
		return (true);
	if (vars.map[pos.y][pos.x - 1] != '1'
		&& empty[(pos.x - 1) + (pos.y * vars.width)] == false
		&& flood_fill(vars, empty, (t_vector2){pos.x - 1, pos.y}, pos2))
		return (true);
	return (false);
}

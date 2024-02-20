/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/15 18:31:31 by lbartels      #+#    #+#                 */
/*   Updated: 2024/02/16 18:24:09 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long.h"

bool	find_path(t_vars vars)
{
	int			i;
	bool		*array;
	t_vector2	pos2;

	array = ft_calloc((vars.width * vars.height), sizeof(bool));
	if (!array)
		return (ft_putstr_fd("malloc error\n", 2), false);
	pos2 = get_cords(vars.map, 'E');
	if (!flood_fill(vars, array, vars.player, pos2))
		return (free(array), false);
	i = 0;
	while (i < vars.coins_count)
	{
		ft_bzero(array, vars.width * vars.height);
		if (!flood_fill(vars, array, vars.player, vars.coins[i]))
			return (free(array), false);
		i++;
	}
	free(array);
	return (true);
}

bool	count_coins(t_vars *vars)
{
	int	i;
	int	j;

	vars->coins_count = 0;
	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'C')
				vars->coins_count++;
			j++;
		}
		i++;
	}
	if (!vars->coins_count)
		return (false);
	return (true);
}

void	get_coins(t_vars *vars)
{
	int	i;
	int	j;

	vars->coins = malloc(vars->coins_count * sizeof(t_vector2));
	if (!vars->coins)
		return ;
	i = 0;
	vars->coins_count = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'C')
			{
				vars->coins[vars->coins_count] = (t_vector2){j, i};
				vars->coins_count++;
			}
			j++;
		}
		i++;
	}
}

bool	map_checker(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (vars->map[i][j])
		{
			if ((i == vars->height || i == 0) && vars->map[i][j] != '1')
				return (false);
			if (vars->map[i][j] == 'P')
				vars->player = (t_vector2){j, i};
			j++;
		}
		if (j != vars->width)
			return (false);
		if (vars->map[i][0] != '1' || vars->map[i][j - 1] != '1')
			return (false);
		i++;
	}
	return (true);
}

int	check_map(t_vars *vars)
{
	if (!count_coins(vars))
		ft_error(2);
	get_coins(vars);
	vars->width = 0;
	while (vars->map[0][vars->width])
		vars->width++;
	vars->height = 0;
	while (vars->map[vars->height])
		vars->height++;
	if (!map_checker(vars) || !find_path(*vars))
	{
		exit_game(vars);
		ft_error(2);
	}
	return (0);
}

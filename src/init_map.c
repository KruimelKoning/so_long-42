/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 14:41:11 by lbartels      #+#    #+#                 */
/*   Updated: 2024/02/16 18:14:15 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long.h"

t_vector2	get_cords(char **map, char thing)
{
	int			i;
	int			j;
	t_vector2	cords;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == thing)
			{
				cords.x = j;
				cords.y = i;
				return (cords);
			}
			j++;
		}
		i++;
	}
	cords.x = 0;
	cords.y = 0;
	return (cords);
}

void	draw_coin(t_vars vars, t_vector2 cords)
{
	int		i;
	double	time;

	time = mlx_get_time();
	i = (int)(time * 100000) % 10;
	if (!(i % 2))
		i = 2;
	else
		i = 3;
	if (mlx_image_to_window(vars.mlx, vars.img[i],
			cords.x * 128, cords.y * 128) < 0)
		mlx_close_window(vars.mlx);
}

void	draw_image(t_vars vars, t_vector2 cords)
{
	if (vars.map[cords.y][cords.x] == '1')
	{
		if (mlx_image_to_window(vars.mlx, vars.img[1],
				cords.x * 128, cords.y * 128) < 0)
			mlx_close_window(vars.mlx);
	}
	else if (mlx_image_to_window(vars.mlx, vars.img[4],
			cords.x * 128, cords.y * 128) < 0)
		mlx_close_window(vars.mlx);
	if (vars.map[cords.y][cords.x] == 'P')
		if (mlx_image_to_window(vars.mlx, vars.img[0],
				cords.x * 128, cords.y * 128) < 0)
			mlx_close_window(vars.mlx);
	if (vars.map[cords.y][cords.x] == 'C')
		draw_coin(vars, cords);
	if (vars.map[cords.y][cords.x] == 'E')
		if (mlx_image_to_window(vars.mlx, vars.img[5],
				cords.x * 128, cords.y * 128) < 0)
			mlx_close_window(vars.mlx);
}

void	init_map(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			draw_image(*vars, (t_vector2){j, i});
			j++;
		}
		i++;
	}
}

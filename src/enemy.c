/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/20 14:10:33 by lbartels      #+#    #+#                 */
/*   Updated: 2024/02/20 15:00:27 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long.h"

void	init_enemy(t_vars *vars)
{
	vars->enemy = get_cords(vars->map, 'X');
	if (!vars->enemy.x)
		return ;
	if (mlx_image_to_window(vars->mlx, vars->img[6],
			vars->enemy.x * 128, vars->enemy.y * 128) < 0)
		mlx_close_window(vars->mlx);
}

void	check_if_dead(t_vars vars)
{
	if (vars.enemy.x == vars.player.x
		&& vars.enemy.y == vars.player.y)
	{
		ft_printf("YOU LOSE\n");
		mlx_close_window(vars.mlx);
	}
}

void	move_enemy(t_vars *vars)
{
	static double	time;
	static int		move;
	static int		dir;

	if (time + 0.85 > mlx_get_time())
		return ;
	move++;
	if (dir != -1)
		dir = 1;
	if (move == 3 || vars->map[vars->enemy.y + dir][vars->enemy.x] == '1'
			|| vars->map[vars->enemy.y + dir][vars->enemy.x] == 'C')
	{
		move = 0;
		dir *= -1;
	}
	if (vars->map[vars->enemy.y + dir][vars->enemy.x] == '1')
		return ;
	if (mlx_image_to_window(vars->mlx, vars->img[6],
			(vars->enemy.x) * 128, (vars->enemy.y + dir) * 128) < 0)
		mlx_close_window(vars->mlx);
	if (mlx_image_to_window(vars->mlx, vars->img[4],
			(vars->enemy.x) * 128, (vars->enemy.y) * 128) < 0)
		mlx_close_window(vars->mlx);
	vars->enemy.y += dir;
	time = mlx_get_time();
}

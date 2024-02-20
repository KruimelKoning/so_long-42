/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 17:26:12 by lbartels      #+#    #+#                 */
/*   Updated: 2024/02/16 16:17:51 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long.h"

void	check_c_or_e(t_vars *vars, int new_x, int new_y)
{
	if (vars->map[new_y][new_x] == 'E' && !vars->coins_count)
	{
		ft_printf("Congratulations!\n");
		mlx_close_window(vars->mlx);
	}
	else if (vars->map[new_y][new_x] == 'C')
	{
		vars->map[new_y][new_x] = '0';
		if (mlx_image_to_window(vars->mlx, vars->img[4],
				(new_x) * 128, (new_y) * 128) < 0)
			mlx_close_window(vars->mlx);
		vars->coins_count--;
	}
}

void	move(t_vars *vars, t_vector2 move)
{
	const int	new_x = vars->player.x + move.x;
	const int	new_y = vars->player.y + move.y;

	if (vars->map[new_y][new_x] == '1')
		return ;
	if (vars->map[new_y][new_x] == 'C' || vars->map[new_y][new_x] == 'E')
		check_c_or_e(vars, new_x, new_y);
	if (mlx_image_to_window(vars->mlx, vars->img[0],
			(new_x) * 128, (new_y) * 128) < 0)
		mlx_close_window(vars->mlx);
	if (mlx_image_to_window(vars->mlx, vars->img[4],
			(vars->player.x) * 128, (vars->player.y) * 128) < 0)
		mlx_close_window(vars->mlx);
	if (vars->map[vars->player.y][vars->player.x] == 'E')
		if (mlx_image_to_window(vars->mlx, vars->img[5],
				(vars->player.x) * 128, (vars->player.y) * 128) < 0)
			mlx_close_window(vars->mlx);
	vars->player = (t_vector2){new_x, new_y};
	vars->step_counter++;
}

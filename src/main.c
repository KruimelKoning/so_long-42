/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/15 18:41:55 by lbartels      #+#    #+#                 */
/*   Updated: 2024/02/20 14:40:44 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long.h"

static void	ft_hook(void *yes)
{
	t_vars			*vars;
	static double	time;
	static int		previous;

	vars = (t_vars *)yes;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (time + 0.20 > mlx_get_time())
		return ;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
		move(vars, (t_vector2){0, -1});
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		move(vars, (t_vector2){-1, 0});
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
		move(vars, (t_vector2){0, 1});
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		move(vars, (t_vector2){1, 0});
	if (vars->step_counter > previous)
		ft_printf("steps:	%d\n", vars->step_counter);
	time = mlx_get_time();
	previous = vars->step_counter;
	time = mlx_get_time();
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		fd;

	if (argc != 2)
		ft_error(1);
	if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".ber", 4))
		ft_error(1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error(4);
	vars.map = make_array(fd, "10CPE\n");
	if (check_map(&vars))
		ft_error(2);
	vars.player = get_cords(vars.map, 'P');
	vars.step_counter = 0;
	load_sprites(&vars);
	init_map(&vars);
	mlx_loop_hook(vars.mlx, &ft_hook, &vars);
	mlx_loop(vars.mlx);
	exit_game(&vars);
	mlx_terminate(vars.mlx);
}

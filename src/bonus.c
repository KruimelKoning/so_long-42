/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bonus.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/16 16:58:59 by lbartels      #+#    #+#                 */
/*   Updated: 2024/02/20 14:58:58 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long.h"

void	load_steps(t_vars *vars)
{
	mlx_texture_t	*texture[11];
	int				i;
	char			str[27];

	ft_strlcpy(str, "./sprites/step_count/0.png", 27);
	i = 0;
	while (i < 10)
	{
		ft_memset(str + 21, i + 48, 1);
		texture[i] = mlx_load_png(str);
		i++;
	}
	texture[10] = mlx_load_png("./sprites/step_count/steps.png");
	if (!free_textures(texture, 11))
		mlx_close_window(vars->mlx);
	i = 0;
	while (i < 11)
	{
		vars->steps[i] = mlx_texture_to_image(vars->mlx, texture[i]);
		i++;
	}
	mlx_image_to_window(vars->mlx, vars->steps[10], 128, 0);
	mlx_image_to_window(vars->mlx, vars->steps[0], 349, 56);
	while (i > 0)
		mlx_delete_texture(texture[--i]);
}

void	display_steps(t_vars vars)
{
	mlx_image_to_window(vars.mlx, vars.img[1], 256, 0);
	if (vars.step_counter < 100)
	{
		if (mlx_image_to_window(vars.mlx,
				vars.steps[vars.step_counter % 10], 349, 56) < 0)
			mlx_close_window(vars.mlx);
		if (vars.step_counter >= 10)
			if (mlx_image_to_window(vars.mlx,
					vars.steps[vars.step_counter / 10], 317, 56) < 0)
				mlx_close_window(vars.mlx);
		return ;
	}
	if (mlx_image_to_window(vars.mlx,
			vars.steps[(vars.step_counter % 100) % 10], 349, 56) < 0)
		mlx_close_window(vars.mlx);
	if (mlx_image_to_window(vars.mlx,
			vars.steps[(vars.step_counter % 100) / 10], 317, 56) < 0)
		mlx_close_window(vars.mlx);
	if (mlx_image_to_window(vars.mlx,
			vars.steps[vars.step_counter / 100], 285, 56) < 0)
		mlx_close_window(vars.mlx);
}

static void	ft_hook(void *yes)
{
	t_vars			*vars;
	static double	time;
	static int		previous;

	vars = (t_vars *)yes;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (vars->enemy.x)
		move_enemy(vars);
	check_if_dead(*vars);
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
		display_steps(*vars);
	time = mlx_get_time();
	previous = vars->step_counter;
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
	vars.map = make_array(fd, "10CPEX\n");
	if (check_map(&vars))
		ft_error(2);
	vars.player = get_cords(vars.map, 'P');
	vars.step_counter = 0;
	load_sprites(&vars);
	init_map(&vars);
	load_steps(&vars);
	init_enemy(&vars);
	mlx_loop_hook(vars.mlx, &ft_hook, &vars);
	mlx_loop(vars.mlx);
	exit_game(&vars);
	mlx_terminate(vars.mlx);
}

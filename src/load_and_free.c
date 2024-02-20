/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_and_free.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/23 17:47:24 by lbartels      #+#    #+#                 */
/*   Updated: 2024/02/20 14:49:57 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

bool	free_textures(mlx_texture_t	**texture, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (!texture[i])
		{
			ft_putstr_fd("Failure loading png\n", 2);
			break ;
		}
		i++;
	}
	if (i == count)
		return (true);
	while (i > 0)
	{
		i--;
		mlx_delete_texture(texture[i]);
	}
	return (false);
}

void	load_sprites(t_vars *vars)
{
	mlx_texture_t	*texture[7];
	int				i;

	texture[0] = mlx_load_png("./sprites/player.png");
	texture[1] = mlx_load_png("./sprites/wall.png");
	texture[2] = mlx_load_png("./sprites/laptop.png");
	texture[3] = mlx_load_png("./sprites/paper.png");
	texture[4] = mlx_load_png("./sprites/background.png");
	texture[5] = mlx_load_png("./sprites/exit.png");
	texture[6] = mlx_load_png("./sprites/enemy.png");
	vars->mlx = mlx_init(vars->width * 128, vars->height * 128, "game", false);
	if (!free_textures(texture, 7) || !vars->mlx)
	{
		exit_game(vars);
		ft_error(3);
	}
	i = 7;
	while (i > 0)
	{
		i--;
		vars->img[i] = mlx_texture_to_image(vars->mlx, texture[i]);
	}
	while (i < 7)
		mlx_delete_texture(texture[i++]);
}

void	exit_game(t_vars *vars)
{
	free(vars->coins);
	free_array(vars->map);
}

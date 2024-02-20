/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 15:20:30 by lbartels      #+#    #+#                 */
/*   Updated: 2024/02/20 14:57:01 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

# include "../MLX42/include/glad/glad.h"
# include "../MLX42/include/KHR/khrplatform.h"
# include "../MLX42/include/lodepng/lodepng.h"
# include "../MLX42/include/MLX42/MLX42_Int.h"

# include <math.h>

# include "../libft/libft.h"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define WHITE "\033[0;37m"

typedef struct vector2{
	int	x;
	int	y;
}	t_vector2;

typedef struct s_vars{
	mlx_t		*mlx;
	mlx_image_t	*img[7];
	mlx_image_t *steps[11];
	t_vector2	player;
	t_vector2	*coins;
	t_vector2	enemy;
	int			height;
	int			width;
	char		**map;
	int			step_counter;
	int			max_coins;
	int			coins_count;
}	t_vars;

int			check_map(t_vars *vars);
void		init_map(t_vars *vars);

void	load_sprites(t_vars *vars);
bool	free_textures(mlx_texture_t	**texture, int count);

char		*str_join(char *dest, char *src);

bool	flood_fill(t_vars vars, bool *empty, t_vector2 pos, t_vector2 pos2);

char		**make_array(int fd, char *allowed);
t_vector2	get_cords(char **map, char thing);
void		move(t_vars *vars, t_vector2 move);
void		draw_image(t_vars vars, t_vector2 cords);

void		init_enemy(t_vars *vars);
void		move_enemy(t_vars *vars);
void		check_if_dead(t_vars vars);

void		ft_error(char error);
void		exit_game(t_vars *vars);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:39:59 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/05 18:57:34 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include "structs.h"
# include "draw_utils.h"
# include "map.h"
# include "mlx42_mng.h"
# include "parseo.h"
# include "player.h"
# include "raycasting.h"
# include "time_mng.h"
# include <GLFW/glfw3.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/**
 * @note ADD MACRO CHECKER
 */

# define BPP sizeof(int32_t)
# define PI 3.1415926535
# define RAD_90_DEG (PI / 2)
# define RAD_180_DEG PI
# define RAD_270_DEG (3 * PI / 2)
# define RAD_360_DEG (2 * PI)
# define ONE_DEGREE 0.0174533 // one degree in radians
# define CUBSIZE 64           // We use bit shifting ( << 6|| >> 6 (2⁶ == 64))
# define BIT_SHIFT ((uint16_t)log2(CUBSIZE))
# define FOG 10
# define FOV 60 // @note check for 360º as light source
# define HALF_FOV (FOV / 2)
# define PIX_COL 16
# define MAX_PLAYER_VIEW_DIST (FOG * CUBSIZE)
# define COLOR_SWAP 0xF5F5F5FF // == 245, 245, 245, 255
# define CEILING_PATH "./src/imgs/lava_64/"
# define CEILING_TEXTURE "LavaF"
# define CEILING_TEX_NUMBER 4
# define FLOOR_PATH "./src/imgs/water_64/"
# define FLOOR_TEXTURE "w_"
# define FLOOR_TEX_NUMBER 8
# define FPS 60
# define SENSIBILITY 0.5
# define PLAYER_SPEED 0.2
# define HALF_POS 0.5
# define MOUSE_SENSIBILITY 0.005f
# define PLAYER_SIZE 0.025f
# define NUM_TILES 25
# define MAP_SIZE 0.25f
# define PLAYER_COLOR 0xFF0000FF
# define WALL_COLOR 0x0000FFFF
# define RAY_COLOR 0x00FF00FF
# define FULL_PATH_DOOR_TEX "./src/imgs/wolftex/wood.png"
# define DOOR_COLOR 0x000000FF
# define OBJ_PATH "./src/imgs/key_64/"
# define OBJ_TEXTURE "k_"
# define OBJ_NUMBER 12

void		re_draw(t_game *game_wrap, t_player *player_info);
void		set_color_from_var(t_color *color, uint32_t color_setted);
void		exit_mlx42(t_game *game_wrap, t_player *player_info, t_dpar *game_d);
uint32_t	get_color_from_struct(t_color *color, uint8_t alpha);

#endif

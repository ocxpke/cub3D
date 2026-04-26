#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <GLFW/glfw3.h>
# include <sys/time.h>
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "structs.h"
# include "mlx42_mng.h"
# include "draw_utils.h"
# include "raycasting.h"
# include "player.h"
# include "map.h"
# include "time_mng.h"
# include "parseo.h"

/**
 * @note ADD MACRO CHECKER
 */

#define BPP sizeof(int32_t)
#define PI 3.1415926535
#define RAD_90_DEG (PI / 2)
#define RAD_180_DEG PI
#define RAD_270_DEG (3 * PI / 2)
#define RAD_360_DEG (2 * PI)
#define ONE_DEGREE 0.0174533 // one degree in radians
#define CUBSIZE 64			 // We can use bit shifting ( << 6 || >> 6 (2⁶ == 64))
#define BIT_SHIFT ((uint16_t)log2(CUBSIZE))
#define FOG 10
#define FOV 60 // @note check for 360º as light source
#define HALF_FOV (FOV / 2)
#define PIX_COL 16
#define MAP_CUB_SIZE 20
#define PLAYER_MAP_SIZE (MAP_CUB_SIZE / 2)
#define MAX_PLAYER_VIEW_DIST (FOG * CUBSIZE)
#define COLOR_SWAP 0xF5F5F5FF
#define CEILING_PATH "./src/imgs/lava_64/"
#define CEILING_TEXTURE "LavaF"
#define CEILING_NUMBER 4
#define FLOOR_PATH "./src/imgs/water_64/"
#define FLOOR_TEXTURE "w_"
#define FLOOR_NUMBER 8
#define FPS 60
#define SENSIBILITY 0.5
#define PLAYER_SPEED 0.2
#define HALF_POS 0.5
#define MOUSE_SENSIBILITY 0.01

void re_draw(t_game *game_wrap, t_player *player_info);
void set_color_from_var(t_color *color, uint32_t color_setted);
void exit_mlx42(t_game *game_wrap);
uint32_t get_color_from_struct(t_color *color, uint8_t alpha);

#endif

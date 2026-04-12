#ifndef CUB3D_H
# define CUB3D_H

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
#define PLAYER_PIX_SIZE (MAP_CUB_SIZE / 2)
#define MAX_PLAYER_VIEW_DIST (FOG * CUBSIZE)
#define CEILING_TEXTURE "Paco"
#define CEILING_NUMBER 1
#define FLOOR_TEXTURE "Paco"
#define FLOOR_NUMBER 1
#define FPS 60
#define SENSIBILITY 0.5

void re_draw(t_game *game_wrap, t_player *player_info);
void exit_mlx42(t_game *game_wrap);

#endif

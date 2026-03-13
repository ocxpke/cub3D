#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <GLFW/glfw3.h>
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "structs.h"
# include "mlx42_mng.h"
# include "draw_utils.h"
# include "raycasting.h"
# include "player.h"
# include "map.h"

#define BPP sizeof(int32_t)
#define PI 3.1415926535
#define PI_90_DEG PI / 2
#define PI_180_DEG PI
#define PI_270_DEG 3 * PI / 2
#define PI_360_DEG 2 * PI
#define ONE_DEGREE 0.0174533 // one degree in radians
#define CUBSIZE 64			 // We can use bit shifting ( << 6 || >> 6 (2⁶ == 64))
#define FOG 10
#define FOV 60 // @note check for 360º as light source
#define HALF_FOV FOV / 2
#define RESOLUTION 16
#define MAP_CUB_SIZE 20
#define PLAYER_PIX_SIZE MAP_CUB_SIZE / 2


void draw_line_simple(t_game *game, float x0, float y0, float x1, float y1, uint32_t color, int mode);
void re_draw(t_game *game_wrap, t_player *player_info);

#endif

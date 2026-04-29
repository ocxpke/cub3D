#ifndef MLX42_MNG_H
# define MLX42_MNG_H

# include "cub3d.h"

void key_hook(void *param);
int manage_mlx42_resources(t_game *game_wrap, t_dpar *game_d);
void resize_hook(int32_t width, int32_t height, void* param);
void check_floor_texture(t_ceil_floor_tex *ceil_floor_tex);
void check_ceiling_texture(t_ceil_floor_tex *ceil_floor_tex);
void mouse_movement_hook(double xpos, double ypos, void *param);

#endif

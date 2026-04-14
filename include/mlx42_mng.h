#ifndef MLX42_MNG_H
# define MLX42_MNG_H

# include "cub3d.h"

void key_hook(void *param);
int manage_mlx42_resources(t_game *game_wrap, t_dpar *game_d);
void resize_hook(int32_t width, int32_t height, void* param);

#endif

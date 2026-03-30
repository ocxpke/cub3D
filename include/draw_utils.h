#ifndef DRAW_UTILS_H
# define DRAW_UTILS_H

# include "cub3d.h"

void draw_line_simple(t_game *game, float x0, float y0, float x1, float y1, uint32_t color, int mode);

void draw_player_view_line(t_game *game, t_player *player_info, float x, float y0, float y1, float wallHitPoint, float wallHitPixel, float steps, float dist);
uint32_t get_color_from_texture(mlx_texture_t *texture, uint16_t x, uint16_t y, float dist);

#endif

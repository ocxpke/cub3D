#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

void draw_rays(t_game *game_wrap, t_player *player_info);
void draw_player_view_line(t_game *game, float x, float y0, float y1, uint32_t color);

#endif

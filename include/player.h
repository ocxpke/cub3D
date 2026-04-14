#ifndef PLAYER_H
#define PLAYER_H

#include "cub3d.h"

void draw_player(t_game *game_wrap, t_player *player_info);
void player_key_movement(t_game *game_wrap, t_player *player_info);
void player_key_rotation(t_game *game_wrap, t_player *player_info);
#endif

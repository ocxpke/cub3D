#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

void draw_player(t_game *game_wrap, t_player *player_info);
void move_forward(t_game *game_wrap, t_player *player_info);
void move_backwards(t_game *game_wrap, t_player *player_info);
void move_to_left(t_game *game_wrap, t_player *player_info);
void move_to_right(t_game *game_wrap, t_player *player_info);
#endif

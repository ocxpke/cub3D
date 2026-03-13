#include "../../include/cub3d.h"

static inline void player_movement(t_game *game_wrap, t_player *player_info, float moveInX, float moveInY)
{
	float marginX;
	float marginY;

	marginX = 0.25;
	marginY = 0.25;
	if (moveInX < 0)
		marginX = -0.25;
	else if (moveInX == 0)
		marginX = 0;
	if (moveInY < 0)
		marginY = -0.25;
	else if (moveInY == 0)
		marginY = 0;
	int nextX = (int)(player_info->posX + moveInX + marginX);
	int nextY = (int)(player_info->posY + moveInY + marginY);
	if (game_wrap->map[(int)player_info->posY][nextX] == '0')
		player_info->posX += moveInX;
	if (game_wrap->map[nextY][(int)player_info->posX] == '0')
		player_info->posY += moveInY;
}

void move_forward(t_game *game_wrap, t_player *player_info)
{
	player_movement(game_wrap, player_info, player_info->dirX, player_info->dirY);
}

void move_backwards(t_game *game_wrap, t_player *player_info)
{
	player_movement(game_wrap, player_info, -1 * player_info->dirX, -1 * player_info->dirY);
}

void move_to_left(t_game *game_wrap, t_player *player_info)
{
	player_movement(game_wrap, player_info, player_info->dirY, -1 * player_info->dirX);
}
void move_to_right(t_game *game_wrap, t_player *player_info)
{
	player_movement(game_wrap, player_info, -1 * player_info->dirY, player_info->dirX);
}

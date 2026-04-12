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

void player_key_movement(t_game *game_wrap, t_player *player_info)
{
	float delta_time = game_wrap->window->delta_time * FPS * SENSIBILITY;
	float len;
	float moveInX = 0;
	float moveInY = 0;

	if (player_info->key_control.w_key)
	{
		moveInX += player_info->deltaX * delta_time;
		moveInY += player_info->deltaY * delta_time;
	}
	if (player_info->key_control.s_key)
	{
		moveInX += -1 * player_info->deltaX * delta_time;
		moveInY += -1 * player_info->deltaY * delta_time;
	}
	if (player_info->key_control.a_key)
	{
		moveInX += player_info->deltaY * delta_time;
		moveInY += -1 * player_info->deltaX * delta_time;
	}
	if (player_info->key_control.d_key)
	{
		moveInX += -1 * player_info->deltaY * delta_time;
		moveInY += player_info->deltaX * delta_time;
	}
	len = sqrt((moveInX * moveInX) + (moveInY * moveInY));
	if ((len > (delta_time * player_info->deltaX)) || (len > player_info->deltaY * delta_time))
	{
		moveInX = (moveInX / len) * delta_time;
		moveInY = (moveInY / len) * delta_time;
	}
	player_movement(game_wrap, player_info, moveInX, moveInY);
}

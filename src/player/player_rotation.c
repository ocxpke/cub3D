#include "../../include/cub3d.h"

void player_key_rotation(t_game *game_wrap, t_player *player_info)
{
	float delta_time = game_wrap->window->delta_time * FPS * SENSIBILITY;
	if (player_info->key_control.left_arrow)
	{
		player_info->ang -= 0.1 * delta_time;
		if (player_info->ang < 0)
			player_info->ang += (2 * PI);
		player_info->deltaX = cos(player_info->ang) * PLAYER_SPEED;
		player_info->deltaY = sin(player_info->ang) * PLAYER_SPEED;
	}
	if (player_info->key_control.right_arrow)
	{
		player_info->ang += 0.1 * delta_time;
		if (player_info->ang > (2 * PI))
			player_info->ang -= (2 * PI);
		player_info->deltaX = cos(player_info->ang) * PLAYER_SPEED;
		player_info->deltaY = sin(player_info->ang) * PLAYER_SPEED;
	}
}

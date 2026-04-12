#include "../../include/cub3d.h"

inline void check_facing_ns(t_player *player_info, float ang)
{
	if (ang > RAD_180_DEG && ang < RAD_360_DEG)
		player_info->look_ns = -1;
	else if (ang < RAD_180_DEG || ang > RAD_360_DEG)
		player_info->look_ns = 1;
	else if (ang == RAD_180_DEG || ang == RAD_360_DEG)
		player_info->look_ns = 0;
}

inline void check_facing_ew(t_player *player_info, float ang)
{
	if (ang > RAD_90_DEG && ang < RAD_270_DEG)
		player_info->look_ew = -1;
	else if (ang < RAD_90_DEG || ang > RAD_270_DEG)
		player_info->look_ew = 1;
	else if (ang == RAD_90_DEG || ang == RAD_270_DEG)
		player_info->look_ew = 0;
}

void player_key_rotation(t_game *game_wrap, t_player *player_info)
{
	float delta_time = game_wrap->window->delta_time * FPS * SENSIBILITY;
	if (player_info->key_control.left_arrow)
	{
		player_info->ang -= 0.1 * delta_time;
		if (player_info->ang < 0)
			player_info->ang += (2 * PI);
		player_info->deltaX = cos(player_info->ang) / 8;
		player_info->deltaY = sin(player_info->ang) / 8;
	}
	if (player_info->key_control.right_arrow)
	{
		player_info->ang += 0.1 * delta_time;
		if (player_info->ang > (2 * PI))
			player_info->ang -= (2 * PI);
		player_info->deltaX = cos(player_info->ang) / 8;
		player_info->deltaY = sin(player_info->ang) / 8;
	}
	check_facing_ns(player_info, player_info->ang);
	check_facing_ew(player_info, player_info->ang);
}

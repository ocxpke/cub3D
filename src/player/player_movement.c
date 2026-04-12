#include "../../include/cub3d.h"

static inline void player_movement(t_game *game_wrap, t_player *player_info, float move_in_x, float move_in_y)
{
	float marginX;
	float marginY;

	marginX = 0.25;
	marginY = 0.25;
	if (move_in_x < 0)
		marginX = -0.25;
	else if (move_in_x == 0)
		marginX = 0;
	if (move_in_y < 0)
		marginY = -0.25;
	else if (move_in_y == 0)
		marginY = 0;
	int nextX = (int)(player_info->posX + move_in_x + marginX);
	int nextY = (int)(player_info->posY + move_in_y + marginY);
	if (game_wrap->map[(int)player_info->posY][nextX] == '0')
		player_info->posX += move_in_x;
	if (game_wrap->map[nextY][(int)player_info->posX] == '0')
		player_info->posY += move_in_y;
}

static inline void calculate_palyer_speed(t_player *player_info, float *move_in_x, float *move_in_y, float delta_time)
{
	if (player_info->key_control.w_key)
	{
		*move_in_x += player_info->deltaX * delta_time;
		*move_in_y += player_info->deltaY * delta_time;
	}
	if (player_info->key_control.s_key)
	{
		*move_in_x += -1 * player_info->deltaX * delta_time;
		*move_in_y += -1 * player_info->deltaY * delta_time;
	}
	if (player_info->key_control.a_key)
	{
		*move_in_x += player_info->deltaY * delta_time;
		*move_in_y += -1 * player_info->deltaX * delta_time;
	}
	if (player_info->key_control.d_key)
	{
		*move_in_x += -1 * player_info->deltaY * delta_time;
		*move_in_y += player_info->deltaX * delta_time;
	}
}

static inline void normalize_speed(t_player *player_info, float *move_in_x, float *move_in_y, float delta_time)
{
	float pressed_key_speed = sqrt(*move_in_x * *move_in_x + *move_in_y * *move_in_y);
	float normal_speed = sqrt(player_info->deltaX * player_info->deltaX +
							  player_info->deltaY * player_info->deltaY) *
						 delta_time;
	if (pressed_key_speed > normal_speed)
	{
		*move_in_x = (*move_in_x / pressed_key_speed) * normal_speed;
		*move_in_y = (*move_in_y / pressed_key_speed) * normal_speed;
	}
}

void player_key_movement(t_game *game_wrap, t_player *player_info)
{
	float delta_time = game_wrap->window->delta_time * FPS * SENSIBILITY;
	float move_in_x = 0;
	float move_in_y = 0;
	calculate_palyer_speed(player_info, &move_in_x, &move_in_y, delta_time);
	normalize_speed(player_info, &move_in_x, &move_in_y, delta_time);
	player_movement(game_wrap, player_info, move_in_x, move_in_y);
}

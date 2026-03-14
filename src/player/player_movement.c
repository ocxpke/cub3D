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

static inline void move_forward(t_game *game_wrap, t_player *player_info)
{
	player_movement(game_wrap, player_info, player_info->dirX, player_info->dirY);
}

static inline void move_backwards(t_game *game_wrap, t_player *player_info)
{
	player_movement(game_wrap, player_info, -1 * player_info->dirX, -1 * player_info->dirY);
}

static inline void move_to_left(t_game *game_wrap, t_player *player_info)
{
	player_movement(game_wrap, player_info, player_info->dirY, -1 * player_info->dirX);
}
static inline void move_to_right(t_game *game_wrap, t_player *player_info)
{
	player_movement(game_wrap, player_info, -1 * player_info->dirY, player_info->dirX);
}

void player_key_movement(t_game *game_wrap, t_player *player_info)
{
	t_keys player_keyboard = player_info->key_control;

	if (player_keyboard.w_key)
		move_forward(game_wrap, player_info);
	if (player_keyboard.s_key)
		move_backwards(game_wrap, player_info);
	if (player_keyboard.a_key)
		move_to_left(game_wrap, player_info);
	if (player_keyboard.d_key)
		move_to_right(game_wrap, player_info);
}

inline void check_facing_ns(t_player *player_info, float ang)
{
	if (ang > PI_180_DEG && ang < PI_360_DEG)
		player_info->look_ns = -1;
	else if (ang < PI_180_DEG || ang > PI_360_DEG)
		player_info->look_ns = 1;
	else if (ang == PI_180_DEG || ang == PI_360_DEG)
		player_info->look_ns = 0;
}

inline void check_facing_ew(t_player *player_info, float ang)
{
	if (ang > PI_90_DEG && ang < PI_270_DEG)
		player_info->look_ew = -1;
	else if (ang < PI_90_DEG || ang > PI_270_DEG)
		player_info->look_ew = 1;
	else if (ang == PI_90_DEG || ang == PI_270_DEG)
		player_info->look_ew = 0;
}

void player_key_rotation(t_player *player_info)
{
	t_keys player_keyboard = player_info->key_control;
	if (player_keyboard.left_arrow)
	{
		player_info->ang -= 0.1;
		if (player_info->ang < 0)
			player_info->ang += (2 * PI);
		player_info->dirX = cos(player_info->ang) / 8;
		player_info->dirY = sin(player_info->ang) / 8;

		check_facing_ns(player_info, player_info->ang);
		check_facing_ew(player_info, player_info->ang);
	}

	if (player_keyboard.right_arrow)
	{
		player_info->ang += 0.1;
		if (player_info->ang > (2 * PI))
			player_info->ang -= (2 * PI);
		player_info->dirX = cos(player_info->ang) / 8;
		player_info->dirY = sin(player_info->ang) / 8;

		check_facing_ns(player_info, player_info->ang);
		check_facing_ew(player_info, player_info->ang);
	}
}

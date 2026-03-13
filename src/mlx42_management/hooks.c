#include "../../include/cub3d.h"

/**
 * @note Ver si esto funciona
 */
void resize_hook(int32_t width, int32_t height, void *param)
{
	t_all *all_things = (t_all *)param;
	mlx_resize_image(all_things->game_wrap->game_view, width, height);
	all_things->game_wrap->map_view->instances[0].x = width - all_things->game_wrap->map_view->width;
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

/**
 * @brief We calculate the distance from point (x0, y0) to point (x1, y1). Pythagorean theorem
 *
 * @note Read more about mlx_key_data_t
 *
 * @param keydata MLX structure that contains all keyboard data needed
 * @param param Here we get one pointer to pass as a param so we pass a wrapper structure
 *
 * @return Void
 */
void key_hook(mlx_key_data_t keydata, void *param)
{
	t_all *all_info = (t_all *)param;

	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		move_forward(all_info->game_wrap, all_info->player_info);
	}

	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		move_backwards(all_info->game_wrap, all_info->player_info);
	}

	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		move_to_left(all_info->game_wrap, all_info->player_info);
	}

	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		move_to_right(all_info->game_wrap, all_info->player_info);
	}

	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		all_info->player_info->ang -= 0.1;
		if (all_info->player_info->ang < 0)
			all_info->player_info->ang += (2 * PI);
		all_info->player_info->dirX = cos(all_info->player_info->ang) / 8;
		all_info->player_info->dirY = sin(all_info->player_info->ang) / 8;

		check_facing_ns(all_info->player_info, all_info->player_info->ang);
		check_facing_ew(all_info->player_info, all_info->player_info->ang);
	}

	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		all_info->player_info->ang += 0.1;
		if (all_info->player_info->ang > (2 * PI))
			all_info->player_info->ang -= (2 * PI); // Por que no simplemente =??
		all_info->player_info->dirX = cos(all_info->player_info->ang) / 8;
		all_info->player_info->dirY = sin(all_info->player_info->ang) / 8;

		check_facing_ns(all_info->player_info, all_info->player_info->ang);
		check_facing_ew(all_info->player_info, all_info->player_info->ang);
	}

	re_draw(all_info->game_wrap, all_info->player_info);
}

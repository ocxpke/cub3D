#include "../../include/cub3d.h"

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
		all_info->player_info->posX += all_info->player_info->dirX;
		all_info->player_info->posY += all_info->player_info->dirY;
	}

	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		all_info->player_info->posX -= all_info->player_info->dirX;
		all_info->player_info->posY -= all_info->player_info->dirY;
	}

	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		all_info->player_info->ang -= 0.1;
		if (all_info->player_info->ang < 0)
			all_info->player_info->ang += (2 * PI);
		all_info->player_info->dirX = cos(all_info->player_info->ang) / 8;
		all_info->player_info->dirY = sin(all_info->player_info->ang) / 8;
	}

	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		all_info->player_info->ang += 0.1;
		if (all_info->player_info->ang > (2 * PI))
			all_info->player_info->ang -= (2 * PI); // Por que no simplemente =??
		all_info->player_info->dirX = cos(all_info->player_info->ang) / 8;
		all_info->player_info->dirY = sin(all_info->player_info->ang) / 8;
	}

	re_draw(all_info->game_wrap, all_info->player_info);
}

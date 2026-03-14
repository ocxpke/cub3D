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
	t_keys *player_keyboard = &(all_info->player_info->key_control);

	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		player_keyboard->w_key = 1;
	}

	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		player_keyboard->s_key = 1;
	}

	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		player_keyboard->a_key = 1;
	}

	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		player_keyboard->d_key = 1;
	}

	// AAAAAAAAAAAAAAAAAAAAAA

	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
	{
		player_keyboard->w_key = 0;
	}

	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
	{
		player_keyboard->s_key = 0;
	}

	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
	{
		player_keyboard->a_key = 0;
	}

	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
	{
		player_keyboard->d_key = 0;
	}

	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		player_keyboard->left_arrow = 1;
	}

	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		player_keyboard->right_arrow = 1;
	}

	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
	{
		player_keyboard->left_arrow = 0;
	}

	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
	{
		player_keyboard->right_arrow = 0;
	}

	re_draw(all_info->game_wrap, all_info->player_info);
}

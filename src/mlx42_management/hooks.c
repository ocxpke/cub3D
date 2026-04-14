#include "../../include/cub3d.h"

/**
 * @note Ver si esto funciona
 */
void resize_hook(int32_t width, int32_t height, void *param)
{
	t_all_structs *all_things = (t_all_structs *)param;
	mlx_resize_image(all_things->game_wrap->game_view, width, height);
	all_things->game_wrap->map_view->instances[0].x = width - all_things->game_wrap->map_view->width;
	all_things->game_wrap->pixels_cols = FOV * PIX_COL;
	if ((FOV * PIX_COL) > width)
		all_things->game_wrap->pixels_cols = width;
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
void key_hook(void *param)
{
	t_all_structs *all_info = (t_all_structs *)param;
	t_keys *player_keyboard = &(all_info->player_info->key_control);

	player_keyboard->w_key = mlx_is_key_down(all_info->game_wrap->window, MLX_KEY_W);
	player_keyboard->s_key = mlx_is_key_down(all_info->game_wrap->window, MLX_KEY_S);
	player_keyboard->a_key = mlx_is_key_down(all_info->game_wrap->window, MLX_KEY_A);
	player_keyboard->d_key = mlx_is_key_down(all_info->game_wrap->window, MLX_KEY_D);
	player_keyboard->left_arrow = mlx_is_key_down(all_info->game_wrap->window, MLX_KEY_LEFT);
	player_keyboard->right_arrow = mlx_is_key_down(all_info->game_wrap->window, MLX_KEY_RIGHT);

	if (mlx_is_key_down(all_info->game_wrap->window, MLX_KEY_ESCAPE))
		return exit_mlx42(all_info->game_wrap);

	re_draw(all_info->game_wrap, all_info->player_info);
}

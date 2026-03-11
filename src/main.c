#include "../include/cub3d.h"

char *MAP[] = {
	"1111111111111111",
	"1000001000000011",
	"1000000100000001",
	"1000000000000011",
	"1000000100100001",
	"1000000000010001",
	"1000000100001001",
	"1000000000000001",
	"1000000100000001",
	"1111111111111111",
	NULL};

/**
 * @brief Initialise every parameter needed
 *
 * @param game_wrap Represents the structure that contains all map content and info needed
 * @param player_info Represents the strcuture that contains all player info needed
 *
 * @return Void
 */
static void set_init_vals(t_game *game_wrap, t_player *player_info)
{
	game_wrap->map = MAP;
	game_wrap->map_height = 10;
	game_wrap->map_width = 16;
	player_info->posX = 4;
	player_info->posY = 2.5;
	player_info->ang = PI_90_DEG;
	player_info->dirX = cos(player_info->ang) / 8;
	player_info->dirY = sin(player_info->ang) / 8;
}

/**
 * @brief This function clears both images (map_view & game_view) and
 * displays a new image, recalculating everything
 *
 * @note If there is something slow when displaying at exec time is in this function
 *
 * @param game_wrap Represents the structure that contains all map content and info needed
 * @param player_info Represents the strcuture that contains all player info needed
 *
 * @return Void
 */
void re_draw(t_game *game_wrap, t_player *player_info)
{
	ft_memset(game_wrap->map_view->pixels, 125, game_wrap->map_view->width * game_wrap->map_view->height * BPP);
	ft_memset(game_wrap->game_view->pixels, 0, game_wrap->game_view->width * game_wrap->game_view->height * BPP);
	draw_map(game_wrap);
	draw_player(game_wrap, player_info);
	// draw_direction(game_wrap, player_info);
	draw_rays(game_wrap, player_info);
}

int main(int argc, char **argv)
{
	t_game game_wrap;
	t_player player_info;
	t_all all;
	(void)argc;
	(void)argv;

	set_init_vals(&game_wrap, &player_info);
	mlx_set_setting(MLX_MAXIMIZED, 1);
	mlx_t *mlx = mlx_init(1, 1, "cub3d", false);
	if (!mlx)
		exit(EXIT_FAILURE);
	take_window_data(&game_wrap);
	mlx_image_t *game_view = mlx_new_image(mlx, game_wrap.init_width, game_wrap.init_heigth);
	if (!game_view || (mlx_image_to_window(mlx, game_view, 0, 0) < 0))
		exit(EXIT_FAILURE);

	/**
	 * @note Revisar los valores hardcodeados
	 */
	mlx_image_t *map_view = mlx_new_image(mlx, 300, 200);
	if (!map_view || (mlx_image_to_window(mlx, map_view, game_wrap.init_width - 300, 0) < 0))
		exit(EXIT_FAILURE);

	// Init game components
	game_wrap.mlx = mlx;
	game_wrap.map_view = map_view;
	game_wrap.game_view = game_view;
	all.game_wrap = &game_wrap;
	all.player_info = &player_info;

	re_draw(&game_wrap, &player_info);
	mlx_key_hook(mlx, key_hook, &all);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

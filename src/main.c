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

char *MAP_WOLF[] = {
	"1111111111111111",
	"1000010000100001",
	"1010010100101001",
	"1011000100001001",
	"1000011111011001",
	"1110110001010011",
	"1000000000000001",
	"1001100001100001",
	"1010111100010011",
	"1111111111111111",
	NULL};

char *MAP_LONG[] = {
	"111111111111111111111111",
	"100000000000000000000001",
	"101111011110111101111001",
	"100001010000100001001001",
	"100001010110101101001001",
	"101111010010100001111001",
	"100000000000000000000001",
	"111111111111111111111111",
	NULL};

/**
 * @brief Initialise every parameter needed
 *
 * @param game_wrap Represents the structure that contains all map content and info needed
 * @param player_info Represents the strcuture that contains all player info needed
 * @return Void
 */
static void set_init_vals(t_game *game_wrap, t_player *player_info)
{
	game_wrap->map = MAP;
	game_wrap->map_height = 10;
	game_wrap->map_width = 16;
	player_info->posX = 4.5;
	player_info->posY = 2.5;
	player_info->ang = RAD_180_DEG;
	player_info->look_ew = 0;
	player_info->deltaX = cos(player_info->ang) / 8;//Por que 8?
	player_info->deltaY = sin(player_info->ang) / 8;
	player_info->key_control.w_key = 0;
	player_info->key_control.s_key = 0;
	player_info->key_control.a_key = 0;
	player_info->key_control.d_key = 0;
	player_info->key_control.left_arrow = 0;
	player_info->key_control.right_arrow = 0;
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
	//No need to clean frame we overwrite ft_memset(game_wrap->game_view->pixels, 0, game_wrap->game_view->width * game_wrap->game_view->height * BPP);
	draw_map(game_wrap);
	player_key_rotation(player_info);
	player_key_movement(game_wrap, player_info);
	//printf("[%d, %d]\n", player_info->look_ns, player_info->look_ew);
	draw_player(game_wrap, player_info);
	draw_rays(game_wrap, player_info);
}

void exit_mlx42(t_game *game_wrap)
{
	mlx_delete_image(game_wrap->window, game_wrap->map_view);
	mlx_delete_image(game_wrap->window, game_wrap->game_view);
	mlx_close_window(game_wrap->window);
	/**
	 * @note frames need to be cleaned
	 */
	mlx_terminate(game_wrap->window);
	exit (0);
}

int main(int argc, char **argv)
{
	t_game game_wrap;
	t_player player_info;
	t_all all;
	(void)argc;
	(void)argv;

	set_init_vals(&game_wrap, &player_info);
	manage_mlx42_resources(&game_wrap);

	// game_wrap.window->delta_time;

	all.game_wrap = &game_wrap;
	all.player_info = &player_info;

	re_draw(&game_wrap, &player_info);
	mlx_resize_hook(game_wrap.window, resize_hook, &all);
	mlx_loop_hook(game_wrap.window, key_hook, &all);
	mlx_loop(game_wrap.window);

	exit_mlx42(&game_wrap);

	return (EXIT_SUCCESS);
}

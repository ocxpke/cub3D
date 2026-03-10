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
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t *mlx = mlx_init(1920, 900, "cub3d", false);
	if (!mlx)
		exit(EXIT_FAILURE);

	mlx_image_t *game_view = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!game_view || (mlx_image_to_window(mlx, game_view, 0, 0) < 0))
		exit(EXIT_FAILURE);

	mlx_image_t *map_view = mlx_new_image(mlx, 300, 200);
	if (!map_view || (mlx_image_to_window(mlx, map_view, mlx->width - 300, 0) < 0))
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

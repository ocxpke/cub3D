/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:14:28 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/15 14:33:15 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief This function clears both images (map_view & game_view) and
 * displays a new image, recalculating everything
 *
 * @note If there is something slow when displaying at exec time
 *is in this function
 *
 * @param game_wrap Represents the structure that contains all
 *map content and info needed
 * @param player_info Represents the strcuture that contains
 *all player info needed
 *
 * @return Void
 */
void re_draw(t_game *game_wrap, t_player *player_info)
{
	player_key_rotation(game_wrap, player_info);
	player_key_movement(game_wrap, player_info);
	if (player_info->p_moves)
	{
		ft_memset(game_wrap->map_view->pixels, 125, game_wrap->map_view->width * game_wrap->map_view->height * BPP);
		draw_player(game_wrap);
		draw_map(game_wrap, player_info);
	}
	draw_rays(game_wrap, player_info);
	draw_sprites(game_wrap, player_info);
	player_info->p_moves = 0;
}

static inline void init_wall_arr_and_full_wrapper(t_all_structs *all,
												  t_dpar *parsing, t_game *game_wrap, t_player *player_info)
{
	player_info->wall_distance = ft_calloc(game_wrap->pixels_cols,
										   sizeof(float));
	if (!player_info->wall_distance)
		exit(EXIT_FAILURE);
	all->game_wrap = game_wrap;
	all->player_info = player_info;
	all->parser_data = parsing;
}

int main(int argc, char **argv)
{
	t_all_structs all;
	t_dpar game_d;
	t_game game_wrap;
	t_player player_info;

	if (!parsing(argc, argv, &game_d))
		return (perror("Something went wrong at parsing"), EXIT_FAILURE);
	set_init_vals(&game_wrap, &player_info, &game_d);
	manage_mlx42_resources(&game_wrap, &game_d);
	load_all_sprites(&game_wrap, &player_info, &game_d);
	init_wall_arr_and_full_wrapper(&all, &game_d, &game_wrap, &player_info);
	re_draw(&game_wrap, &player_info);
	mlx_resize_hook(game_wrap.window, resize_hook, &all);
	mlx_cursor_hook(game_wrap.window, mouse_movement_hook, &all);
	mlx_loop_hook(game_wrap.window, key_hook, &all);
	mlx_loop(game_wrap.window);
	exit_mlx42(&game_wrap, &player_info, &game_d);
	return (EXIT_SUCCESS);
}

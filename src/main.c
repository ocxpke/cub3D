/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:14:28 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/13 14:34:57 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief We take the color values from
 *
 * @param color Struct cotaining the Red, Green, and Blue values
 * @param alpha The corresponding alpha value, for opacity
 *
 * @return The color in the corresponding uint32_t
 */
inline void	set_color_from_var(t_color *color, uint32_t color_setted)
{
	color->red = (color_setted >> 24) & 0xFF;
	color->green = (color_setted >> 16) & 0xFF;
	color->blue = (color_setted >> 8) & 0xFF;
	color->alpha = color_setted & 0xFF;
}

/**
 * @brief We take the color from the struct and set an uint32_t value
 *that we can use later
 *
 * @param color Struct cotaining the Red, Green, and Blue values
 * @param alpha The corresponding alpha value, for opacity
 *
 * @return The color in the corresponding uint32_t
 */
inline uint32_t	get_color_from_struct(t_color *color, uint8_t alpha)
{
	uint32_t	ret_color;

	ret_color = ((uint32_t)color->red << 24);
	ret_color |= ((uint32_t)color->green << 16);
	ret_color |= ((uint32_t)color->blue << 8);
	ret_color |= ((uint32_t)alpha);
	return (ret_color);
}

/**
 * @brief We set player orientation into the corresponding radians
 *
 * @note North/south logic is not inverted, optical ilussion.
 * @param player_info Struct containing all player info needed
 * @param map_info Struct containing all map info needed
 *
 * @return Void
 */
static void	set_orientation(t_player *player_info, t_map *map_info)
{
	if (map_info->pstart_orientation == 'N')
		player_info->ang = RAD_90_DEG;
	else if (map_info->pstart_orientation == 'S')
		player_info->ang = RAD_270_DEG;
	else if (map_info->pstart_orientation == 'E')
		player_info->ang = RAD_180_DEG;
	else if (map_info->pstart_orientation == 'W')
		player_info->ang = RAD_360_DEG;
	else
		write(STDERR_FILENO, "Error at set_orientation", 24);
}

/**
 * @brief Initialise every parameter needed
 *
 * @param game_wrap Represents the structure that contains all map
 * content and info needed
 * @param player_info Represents the strcuture that contains
 * all player info needed
 * @return Void
 */
static void	set_init_vals(t_game *game_wrap, t_player *player_info,
		t_dpar *game_d)
{
	game_wrap->map = game_d->map_s->map;
	game_wrap->map_height = game_d->map_s->rows;
	game_wrap->map_width = game_d->map_s->cols;
	player_info->posx = game_d->map_s->pstart_x + HALF_POS;
	player_info->posy = game_d->map_s->pstart_y + HALF_POS;
	set_orientation(player_info, game_d->map_s);
	player_info->deltax = cos(player_info->ang) * PLAYER_SPEED;
	player_info->deltay = sin(player_info->ang) * PLAYER_SPEED;
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
void	re_draw(t_game *game_wrap, t_player *player_info)
{
	ft_memset(game_wrap->map_view->pixels, 125, game_wrap->map_view->width
		* game_wrap->map_view->height * BPP);
	draw_player(game_wrap);
	draw_map(game_wrap, player_info);
	player_key_rotation(game_wrap, player_info);
	player_key_movement(game_wrap, player_info);
	draw_rays(game_wrap, player_info);
}

/**
 * @note frames need to be cleaned
 */
void	exit_mlx42(t_game *game_wrap)
{
	mlx_delete_image(game_wrap->window, game_wrap->map_view);
	mlx_delete_image(game_wrap->window, game_wrap->game_view);
	mlx_close_window(game_wrap->window);
	mlx_terminate(game_wrap->window);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_dpar			game_d;
	t_game			game_wrap;
	t_player		player_info;
	t_all_structs	all;

	if (!parsing(argc, argv, &game_d))
		return (perror("Something went wrong at parsing"), EXIT_FAILURE);
	printf(H_R"\n\n---------------------not mine!-----------------\n\n"RES);
	set_init_vals(&game_wrap, &player_info, &game_d);
	manage_mlx42_resources(&game_wrap, &game_d);
	all.game_wrap = &game_wrap;
	all.player_info = &player_info;
	all.parser_data = &game_d;
	re_draw(&game_wrap, &player_info);
	mlx_resize_hook(game_wrap.window, resize_hook, &all);
	mlx_cursor_hook(game_wrap.window, mouse_movement_hook, &all);
	mlx_loop_hook(game_wrap.window, key_hook, &all);
	mlx_loop(game_wrap.window);
	exit_mlx42(&game_wrap);
	printf(H_B"\n\n---------------------mine!-----------------\n\n"RES);
	free_map(&game_d);
	free_key_array(&game_d);
	free_up_to_cheklist(&game_d);
	return (EXIT_SUCCESS);
}

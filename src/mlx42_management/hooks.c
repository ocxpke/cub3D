/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:23:57 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/11 19:10:55 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_all_structs	*all_things;
	t_game			*g_wrp;

	all_things = (t_all_structs *)param;
	g_wrp = all_things->game_wrap;
	mlx_resize_image(g_wrp->game_view, width, height);
	mlx_resize_image(g_wrp->map_view, width * MAP_SIZE, height * MAP_SIZE);
	g_wrp->map_view->instances[0].x = width - g_wrp->map_view->width;
	g_wrp->col_gross = g_wrp->game_view->width / (FOV * PIX_COL);
	if (g_wrp->col_gross < 1)
		g_wrp->col_gross = 1;
	g_wrp->pixels_cols = g_wrp->game_view->width / g_wrp->col_gross;
	free(all_things->player_info->wall_distance);
	all_things->player_info->wall_distance = ft_calloc(1, sizeof(float)
			* g_wrp->pixels_cols);
	if (!all_things->player_info->wall_distance)
		exit(EXIT_FAILURE);
}

/**
 * @brief We calculate the distance from point (x0, y0) to point (x1,
 * y1). Pythagorean theorem
 *
 * @note Read more about mlx_key_data_t
 *
 * @param keydata MLX structure that contains all keyboard data needed
 * @param param Here we get one pointer to pass as a param so we pass
 * a wrapper structure
 *
 * @return Void
 */
void	key_hook(void *param)
{
	t_all_structs	*all_info;
	t_keys			*player_keyboard;

	all_info = (t_all_structs *)param;
	player_keyboard = &(all_info->player_info->key_control);
	player_keyboard->w_key = mlx_is_key_down(all_info->game_wrap->window,
			MLX_KEY_W);
	player_keyboard->s_key = mlx_is_key_down(all_info->game_wrap->window,
			MLX_KEY_S);
	player_keyboard->a_key = mlx_is_key_down(all_info->game_wrap->window,
			MLX_KEY_A);
	player_keyboard->d_key = mlx_is_key_down(all_info->game_wrap->window,
			MLX_KEY_D);
	player_keyboard->left_arrow = mlx_is_key_down(all_info->game_wrap->window,
			MLX_KEY_LEFT);
	player_keyboard->right_arrow = mlx_is_key_down(all_info->game_wrap->window,
			MLX_KEY_RIGHT);
	if (mlx_is_key_down(all_info->game_wrap->window, MLX_KEY_ESCAPE))
		return (exit_mlx42(all_info->game_wrap, all_info->player_info,
				all_info->parser_data));
	re_draw(all_info->game_wrap, all_info->player_info);
}

void	mouse_movement_hook(double xpos, double ypos, void *param)
{
	t_all_structs	*all_st;
	float			centerx;
	float			centery;
	float			deltax;
	float			delta_time;

	(void)ypos;
	all_st = (t_all_structs *)param;
	centerx = all_st->game_wrap->game_view->width / 2;
	centery = all_st->game_wrap->game_view->height / 2;
	deltax = xpos - centerx;
	delta_time = all_st->game_wrap->window->delta_time * FPS
		* MOUSE_SENSIBILITY;
	all_st->player_info->p_moves = 1;
	if (deltax > 0)
		rotate_player_right(all_st->player_info, delta_time * deltax);
	else if (deltax < 0)
		rotate_player_left(all_st->player_info, delta_time * (deltax * -1));
	mlx_set_mouse_pos(all_st->game_wrap->window, (int32_t)centerx,
		(int32_t)centery);
}

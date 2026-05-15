/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:11:08 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/15 15:35:32 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	delete_object_tex(t_game *game_wrap)
{
	int	i;

	i = 0;
	if (game_wrap->obj_num == 0)
		return ;
	while (i < OBJ_NUMBER)
	{
		mlx_delete_texture(game_wrap->obj_textures[i]);
		i++;
	}
	free(game_wrap->obj_textures);
	free(game_wrap->obj_info);
}

void	delete_floor_ceiling_tex(t_ceil_floor_tex *ceil_tex,
		t_ceil_floor_tex *floor_tex)
{
	int	i;

	i = 0;
	if (ceil_tex->type == IMAGE_TEXTURE)
	{
		while (i < CEILING_TEX_NUMBER)
		{
			mlx_delete_texture(ceil_tex->all_textures[i]);
			i++;
		}
		free(ceil_tex->all_textures);
	}
	if (floor_tex->type == IMAGE_TEXTURE)
	{
		i = 0;
		while (i < FLOOR_TEX_NUMBER)
		{
			mlx_delete_texture(floor_tex->all_textures[i]);
			i++;
		}
		free(floor_tex->all_textures);
	}
}

static void	delete_wall_tex(t_wall_textures *wall_text)
{
	mlx_delete_texture(wall_text->door_tex);
	mlx_delete_texture(wall_text->north_tex);
	mlx_delete_texture(wall_text->south_tex);
	mlx_delete_texture(wall_text->east_tex);
	mlx_delete_texture(wall_text->west_tex);
}

/**
 * @brief The final function,
	previous to close all the MLX items we free everything
 *
 * @note frames need to be cleaned
 *
 * @param game_wrap All info needed for rendering the game
 * @param player_info All info related to player (movement, pos, etc)
 * @param game_d All parser information
 *
 * @return Void
 */
void	exit_mlx42(t_game *game_wrap, t_player *player_info, t_dpar *game_d)
{
	delete_object_tex(game_wrap);
	delete_floor_ceiling_tex(&(game_wrap->ceiling_tex),
		&(game_wrap->floor_tex));
	delete_wall_tex(&(game_wrap->wall_text));
	mlx_delete_image(game_wrap->window, game_wrap->map_view);
	mlx_delete_image(game_wrap->window, game_wrap->game_view);
	mlx_close_window(game_wrap->window);
	mlx_terminate(game_wrap->window);
	free_map(game_d);
	free_key_array(game_d);
	free_up_to_cheklist(game_d);
	free(player_info->wall_distance);
	exit(EXIT_SUCCESS);
}

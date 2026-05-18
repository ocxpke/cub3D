/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:08:21 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/18 16:26:08 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline void	init_const_values(t_game *game_wrap)
{
	t_const_vals	*aux;

	aux = &(game_wrap->const_values);
	aux->bit_shift = (uint16_t)log2(CUBSIZE);
	aux->rad_90_deg = PI / 2;
	aux->rad_180_deg = PI;
	aux->rad_270_deg = (PI * 3) / 2;
	aux->rad_360_deg = PI * 2;
	aux->half_fov = FOV / 2;
	aux->max_player_view_dist = FOG * CUBSIZE;
	aux->bpp = sizeof(int32_t);
}

/**
 * @brief Just a function that checks all macros have the correct values
 *
 * @return Void
 */
// inline void	macro_checker(void)
// {
// 	if (CUBSIZE <= 0 || (CUBSIZE & (CUBSIZE - 1)) != 0)
// 		return (write(STDERR_FILENO, "Check macros\n", 13), exit(EXIT_FAILURE));
// 	if (FOV <= 0 || FOV > 360 || FPS <= 0 || HALF_FOV <= 0 || FOG <= 0
// 		|| PIX_COL <= 0 || NUM_TILES <= 0)
// 		return (write(STDERR_FILENO, "Check macros\n", 13), exit(EXIT_FAILURE));
// 	if (!(CEILING_TEX_NUMBER > 0) || !(FLOOR_TEX_NUMBER > 0)
// 		|| !(OBJ_NUMBER > 0))
// 		return (write(STDERR_FILENO, "Check macros\n", 13), exit(EXIT_FAILURE));
// 	if (MOUSE_SENSIBILITY <= 0.0f || MOUSE_SENSIBILITY >= 0.5f)
// 		return (write(STDERR_FILENO, "Check macros\n", 13), exit(EXIT_FAILURE));
// 	if (PLAYER_SPEED <= 0.0f || PLAYER_SPEED >= 1.0f)
// 		return (write(STDERR_FILENO, "Check macros\n", 13), exit(EXIT_FAILURE));
// 	if (SENSIBILITY <= 0.0f)
// 		return (write(STDERR_FILENO, "Check macros\n", 13), exit(EXIT_FAILURE));
// 	if (MAP_SIZE <= 0.0f || MAP_SIZE >= 1.0f)
// 		return (write(STDERR_FILENO, "Check macros\n", 13), exit(EXIT_FAILURE));
// 	if (PLAYER_SIZE <= 0.0f || PLAYER_SIZE >= 1.0f)
// 		return (write(STDERR_FILENO, "Check macros\n", 13), exit(EXIT_FAILURE));
// }

/**
 * @brief We set player orientation into the corresponding radians
 *
 * @note North/south logic is not inverted, optical ilussion.
 * @param player_info Struct containing all player info needed
 * @param map_info Struct containing all map info needed
 *
 * @return Void
 */
static inline void	set_orientation(t_const_vals const_vals,
		t_player *player_info, t_map *map_info)
{
	if (map_info->pstart_orientation == 'N')
		player_info->ang = const_vals.rad_90_deg;
	else if (map_info->pstart_orientation == 'S')
		player_info->ang = const_vals.rad_270_deg;
	else if (map_info->pstart_orientation == 'E')
		player_info->ang = const_vals.rad_180_deg;
	else if (map_info->pstart_orientation == 'W')
		player_info->ang = const_vals.rad_360_deg;
	else
		return (write(STDERR_FILENO, "Error at set_orientation", 24),
			exit(EXIT_FAILURE));
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
void	set_init_vals(t_game *game_wrap, t_player *player_info, t_dpar *game_d)
{
	game_wrap->map = game_d->map_s->map;
	game_wrap->map_height = game_d->map_s->rows;
	game_wrap->map_width = game_d->map_s->cols;
	player_info->posx = game_d->map_s->pstart_x + HALF_POS;
	player_info->posy = game_d->map_s->pstart_y + HALF_POS;
	set_orientation(game_wrap->const_values, player_info, game_d->map_s);
	player_info->deltax = cos(player_info->ang) * PLAYER_SPEED;
	player_info->deltay = sin(player_info->ang) * PLAYER_SPEED;
	player_info->key_control.w_key = 0;
	player_info->key_control.s_key = 0;
	player_info->key_control.a_key = 0;
	player_info->key_control.d_key = 0;
	player_info->key_control.left_arrow = 0;
	player_info->key_control.right_arrow = 0;
	player_info->p_moves = 1;
	init_const_values(game_wrap);
}

static inline void	load_obj_texture(t_game *game_wrap, const char *path_name,
		int num)
{
	char	*full_path;
	char	*num_ext;

	num_ext = num_and_extension(num, TEXTURE_EXT);
	if (!num_ext)
		exit(EXIT_FAILURE);
	full_path = ft_calloc(1, ft_strlen(path_name) + ft_strlen(num_ext) + 1);
	ft_strlcat(full_path, path_name, ft_strlen(path_name) + ft_strlen(num_ext)
		+ 1);
	ft_strlcat(full_path, num_ext, ft_strlen(path_name) + ft_strlen(num_ext)
		+ 1);
	game_wrap->obj_textures[num - 1] = mlx_load_png(full_path);
	free(num_ext);
	free(full_path);
}

void	load_all_obj_textures(t_game *game_wrap)
{
	char	*path_name;
	int		i;

	path_name = ft_calloc(1, ft_strlen(OBJ_PATH) + ft_strlen(OBJ_TEXTURE) + 1);
	if (!path_name)
		exit(EXIT_FAILURE);
	ft_strlcat(path_name, OBJ_PATH, ft_strlen(OBJ_PATH) + ft_strlen(OBJ_TEXTURE)
		+ 1);
	ft_strlcat(path_name, OBJ_TEXTURE, ft_strlen(OBJ_PATH)
		+ ft_strlen(OBJ_TEXTURE) + 1);
	game_wrap->obj_textures = (mlx_texture_t **)ft_calloc(OBJ_NUMBER,
			sizeof(mlx_texture_t *));
	if (!game_wrap->obj_textures)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < OBJ_NUMBER)
	{
		load_obj_texture(game_wrap, path_name, i + 1);
		i++;
	}
	free(path_name);
}

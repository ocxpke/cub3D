/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:08:21 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/13 14:44:28 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
static inline void set_orientation(t_player *player_info, t_map *map_info)
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
void set_init_vals(t_game *game_wrap, t_player *player_info, t_dpar *game_d)
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

static inline void load_obj_texture(t_game *game_wrap, const char *path_name, int num)
{
	char *full_path;
	char *num_ext;

	num_ext = num_and_extension(num, TEXTURE_EXT);
	if (!num_ext)
		exit(EXIT_FAILURE);
	full_path = ft_calloc(1, ft_strlen(path_name) + ft_strlen(num_ext) + 1);
	ft_strlcat(full_path, path_name, ft_strlen(path_name) + ft_strlen(num_ext) + 1);
	ft_strlcat(full_path, num_ext, ft_strlen(path_name) + ft_strlen(num_ext) + 1);
	game_wrap->obj_textures[num - 1] = mlx_load_png(full_path);
	free(num_ext);
	free(full_path);
}

static void load_all_obj_textures(t_game *game_wrap)
{
	char *path_name;
	int i;

	path_name = ft_calloc(1, ft_strlen(OBJ_PATH) + ft_strlen(OBJ_TEXTURE) + 1);
	if (!path_name)
		exit(EXIT_FAILURE);
	ft_strlcat(path_name, OBJ_PATH, ft_strlen(OBJ_PATH) + ft_strlen(OBJ_TEXTURE) + 1);
	ft_strlcat(path_name, OBJ_TEXTURE, ft_strlen(OBJ_PATH) + ft_strlen(OBJ_TEXTURE) + 1);
	game_wrap->obj_textures = (mlx_texture_t **)ft_calloc(OBJ_NUMBER, sizeof(mlx_texture_t *));
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

void load_all_sprites(t_game *game_wrap, t_dpar *pars)
{
	int i;
	t_map *map_s;

	map_s = pars->map_s;
	game_wrap->obj_info = (t_object_info *)ft_calloc(map_s->key_count, sizeof(t_object_info));
	if (!game_wrap->obj_info)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < map_s->key_count)
	{
		game_wrap->obj_info[i].x_pos = map_s->keys_arr[i].k_posx + HALF_POS;
		game_wrap->obj_info[i].y_pos = map_s->keys_arr[i].k_posy + HALF_POS;
		game_wrap->obj_info[i].z_pos = 0;
		game_wrap->obj_info[i].state = 1;
		game_wrap->obj_info[i].type = OBJECT;
		i++;
	}
	load_all_obj_textures(game_wrap);
	game_wrap->obj_num = map_s->key_count;
}

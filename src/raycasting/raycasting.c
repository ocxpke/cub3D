/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:18:03 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/05 18:32:21 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief We calculate the distance from point (x0, y0) to point (x1,
	y1). Pythagorean theorem
 *
 * @param x0 First point X axis value
 * @param y0 First point Y axis value
 * @param x1 Second point X axis value
 * @param y1 Second point Y axis value
 *
 * @return The distance calculated
 */
static inline float dist(float x0, float y0, float x1, float y1)
{
	return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

void draw_sprites(t_game *game_wrap, t_player *player_info)
{
	t_object_info obj;
	obj.obj_texture = mlx_load_png("./src/imgs/key_64/k_7.png");
	if (!obj.obj_texture)
		exit(1);

	obj.x_pos = 4.4f;
	obj.y_pos = 4.4f;

	float dx = obj.x_pos - player_info->posx;
	float dy = obj.y_pos - player_info->posy;

	float cs = cos(player_info->ang);
	float sn = sin(player_info->ang);

	float depth = dx * cs + dy * sn;
	float horizontal = -dx * sn + dy * cs;

	if (depth <= 0.1f)
		return;

	float angle_to_sprite = atan2f(horizontal, depth);
	float screen_x = (angle_to_sprite / (ONE_DEGREE * HALF_FOV)) * (game_wrap->game_view->width / 2.0f) + (game_wrap->game_view->width / 2.0f);
	int sprite_size = (int)(game_wrap->game_view->height / depth);
	float screen_y = game_wrap->game_view->height / 2.0f + sprite_size / 4.0f;
	int half_s = sprite_size / 2;

	float dist_ratio = (dist(player_info->posx, player_info->posy, obj.x_pos, obj.y_pos) * CUBSIZE) / MAX_PLAYER_VIEW_DIST;
	if (dist_ratio > 1.0f)
		dist_ratio = 1.0f;
	float intensity = 0.9f - (dist_ratio * 0.8f);

	for (int i = 0; i < sprite_size; i++)
	{
		int px = (int)screen_x - half_s + i;
		if (px < 0 || px >= (int)game_wrap->game_view->width)
			continue;

		if (player_info->wall_distance[px / game_wrap->col_gross] < (depth * CUBSIZE))
			continue;

		int tex_x = (int)((float)i / sprite_size * obj.obj_texture->width);

		for (int j = 0; j < sprite_size; j++)
		{
			int py = (int)screen_y - half_s + j;
			if (py < 0 || py >= (int)game_wrap->game_view->height)
				continue;

			int tex_y = (int)((float)j / sprite_size * obj.obj_texture->height);

			uint32_t color = get_color_from_texture(obj.obj_texture, tex_x, tex_y, 0);

			if (color != 0xFF00FFFF)
			{
				uint32_t final_color = ((uint32_t)(((color >> 24) & 0xFF) * intensity) << 24);
				final_color |= ((uint32_t)(((color >> 16) & 0xFF) * intensity) << 16);
				final_color |= ((uint32_t)(((color >> 8) & 0xFF) * intensity) << 8);
				final_color |= 0xFF;
				mlx_put_pixel(game_wrap->game_view, px, py, final_color);
			}
		}
	}
}

/**
 * @brief Here we check if the angle passed as a parameter has got out of bounds
 *
 * @param angle The angle to be check
 *
 * @return Void
 */
inline void check_angle_bounds(float *angle)
{
	if (*angle < 0)
		*angle += RAD_360_DEG;
	else if (*angle > RAD_360_DEG)
		*angle -= RAD_360_DEG;
}

/**
 * @brief Just a function to initialize values for the raycast struct
 *
 * @param player_info Struct that has all player usefull information
 * @param raycast All variables that we need to initialize are here
 *
 * @return Void
 */
static inline void init_raycast_values(t_player *player_info,
									   t_raycast *raycast)
{
	raycast->player_angle = player_info->ang;
	raycast->player_posx_cube = player_info->posx * CUBSIZE;
	raycast->player_posy_cube = player_info->posy * CUBSIZE;
	raycast->player_posx_map = player_info->posx;
	raycast->player_posy_map = player_info->posy;
	raycast->horizontal_dist = 100000;
	raycast->vertical_dist = 100000;
	raycast->ray_ct = 0;
	raycast->ray_x = 0;
	raycast->ray_y = 0;
	raycast->ray_x_offset = 0;
	raycast->ray_y_offset = 0;
	raycast->ceil_frame = (get_time() / 150) % CEILING_TEX_NUMBER;
	raycast->floor_frame = (get_time() / 150) % FLOOR_TEX_NUMBER;
}

/**
 * @brief This fucntion help us identifying the collision against a wall,
 * consists of trying to check if we got out of map or if
 * we colide against a wall.
 *
 * @param game_wrap Struct containing all game info
 * @param rc Struct containing all raycaster previously calculated values
 *
 * @return Void
 */
static inline void check_distance_of_field(t_game *game_wrap, t_raycast *rc, uint8_t mode)
{
	t_coll_tex aux;

	aux = WALL_TEX;
	while (rc->distance_of_field < FOG)
	{
		rc->map_x = (int)(rc->ray_x) >> BIT_SHIFT;
		rc->map_y = (int)(rc->ray_y) >> BIT_SHIFT;
		if ((rc->map_x >= 0 && rc->map_x < game_wrap->map_width) && (rc->map_y >= 0 && rc->map_y < game_wrap->map_height) && ((game_wrap->map[rc->map_y][rc->map_x] == '1') || game_wrap->map[rc->map_y][rc->map_x] == 'P'))
		{
			rc->distance_of_field = FOG;
			aux = WALL_TEX;
			if (game_wrap->map[rc->map_y][rc->map_x] == 'P')
				aux = DOOR_TEX;
		}
		else
		{
			rc->ray_x += rc->ray_x_offset;
			rc->ray_y += rc->ray_y_offset;
			rc->distance_of_field += 1;
		}
	}
	if (!mode)
		rc->coll_tex_hor = aux;
	else
		rc->coll_tex_ver = aux;
}

/**
 * @brief Here we check the length of the horizontal rays, we calculate it
 * taking the ray angle value, to check where the ray is going,
	calculating the offset,
 * and then calling the check distance of field func.
 *
 * @note APRECIATE HOW FLOAT WORKS --> -0.01f (ALWAYS 7 DIGITS)
 *
 * @param game_wrap Struct containing all game info
 * @param rc Struct were we will safe our computed values
 *
 * @return Void
 */
static inline void check_horizontal_ray(t_game *game_wrap, t_raycast *rc)
{
	rc->distance_of_field = 0;
	if (tan(rc->ray_angle) == 0)
		rc->ray_angle += 0.0001f;
	rc->arc_tan = -1 / tan(rc->ray_angle);
	if (rc->ray_angle > PI)
	{
		rc->ray_y = (((int)rc->player_posy_cube >> BIT_SHIFT) << BIT_SHIFT) - 0.01f;
		rc->ray_x = (rc->player_posy_cube - rc->ray_y) * rc->arc_tan + rc->player_posx_cube;
		rc->ray_y_offset = -1 * CUBSIZE;
		rc->ray_x_offset = -1 * rc->ray_y_offset * rc->arc_tan;
	}
	if (rc->ray_angle < PI)
	{
		rc->ray_y = (((int)rc->player_posy_cube >> BIT_SHIFT) << BIT_SHIFT) + CUBSIZE;
		rc->ray_x = (rc->player_posy_cube - rc->ray_y) * rc->arc_tan + rc->player_posx_cube;
		rc->ray_y_offset = CUBSIZE;
		rc->ray_x_offset = -1 * rc->ray_y_offset * rc->arc_tan;
	}
	if (rc->ray_angle == 0 || rc->ray_angle == PI)
	{
		rc->ray_x = rc->player_posx_cube;
		rc->ray_y = rc->player_posy_cube;
		rc->distance_of_field = FOG;
	}
	check_distance_of_field(game_wrap, rc, 0);
	rc->horizontal_dist = dist(rc->player_posx_cube, rc->player_posy_cube,
							   rc->ray_x, rc->ray_y);
	rc->horizontal_x = rc->ray_x;
	rc->horizontal_y = rc->ray_y;
}

/**
 * @brief Here we check the length of the vertical rays, we calculate it
 * taking the ray angle value, to check where the ray is going,
	calculating the offset,
 * and then calling the check distance of field func.
 *
 * @note APRECIATE HOW FLOAT WORKS --> -0.01f (ALWAYS 7 DIGITS)
 *
 * @param game_wrap Struct containing all game info
 * @param rc Struct were we will safe our computed values
 *
 * @return Void
 */
static inline void check_vertical_ray(t_game *game_wrap, t_raycast *rc)
{
	rc->distance_of_field = 0;
	if (tan(rc->ray_angle) == 0)
		rc->ray_angle += 0.00001;
	rc->neg_tan = -1 * tan(rc->ray_angle);
	if (rc->ray_angle > RAD_90_DEG && rc->ray_angle < RAD_270_DEG)
	{
		rc->ray_x = (((int)rc->player_posx_cube >> BIT_SHIFT) << BIT_SHIFT) - 0.01f;
		rc->ray_y = (rc->player_posx_cube - rc->ray_x) * rc->neg_tan + rc->player_posy_cube;
		rc->ray_x_offset = -CUBSIZE;
		rc->ray_y_offset = -rc->ray_x_offset * rc->neg_tan;
	}
	if (rc->ray_angle < RAD_90_DEG || rc->ray_angle > RAD_270_DEG)
	{
		rc->ray_x = (((int)rc->player_posx_cube >> BIT_SHIFT) << BIT_SHIFT) + CUBSIZE;
		rc->ray_y = (rc->player_posx_cube - rc->ray_x) * rc->neg_tan + rc->player_posy_cube;
		rc->ray_x_offset = CUBSIZE;
		rc->ray_y_offset = -rc->ray_x_offset * rc->neg_tan;
	}
	if (rc->ray_angle == 0 || rc->ray_angle == PI)
	{
		rc->ray_x = rc->player_posx_cube;
		rc->ray_y = rc->player_posy_cube;
		rc->distance_of_field = FOG;
	}
	check_distance_of_field(game_wrap, rc, 1);
	rc->vertical_dist = dist(rc->player_posx_cube, rc->player_posy_cube,
							 rc->ray_x, rc->ray_y);
	rc->vertical_x = rc->ray_x;
	rc->vertical_y = rc->ray_y;
}

/**
 * @brief Having horizontal and vertical ray lengths computed we check which
 * one is the minor one, which will be the one to be drawed.
 *
 * @param raycast Struct containing all raycaster previously calculated values
 *
 * @return Void
 */
static inline void check_minor_distance(t_raycast *raycast)
{
	if (raycast->horizontal_dist <= raycast->vertical_dist)
	{
		raycast->ray_x = raycast->horizontal_x;
		raycast->ray_y = raycast->horizontal_y;
		raycast->minor_distance = raycast->horizontal_dist;
		raycast->hor_ver = 1;
		raycast->texture_x_hp = raycast->ray_x / CUBSIZE;
		raycast->coll_tex = raycast->coll_tex_hor;
	}
	else
	{
		raycast->ray_x = raycast->vertical_x;
		raycast->ray_y = raycast->vertical_y;
		raycast->minor_distance = raycast->vertical_dist;
		raycast->hor_ver = -1;
		raycast->texture_x_hp = raycast->ray_y / CUBSIZE;
		raycast->coll_tex = raycast->coll_tex_ver;
	}
}

/**
 * @brief Here we will fix the fish eye efect cause by the con/sin function,
 * and by their sinusoidal behavior.
 *
 * @note We save the wall distance to check if the object is in front or behind
 *
 * @param player_info Struct containing all player usefull informaion
 * @param raycast Struct containing all raycaster previously calculated values
 *
 * @return Void
 */
static inline void fix_fish_eye(t_player *player_info, t_raycast *raycast)
{
	raycast->corrected_angle = player_info->ang - raycast->ray_angle;
	check_angle_bounds(&raycast->corrected_angle);
	raycast->minor_distance = raycast->minor_distance * cos(raycast->corrected_angle);
	player_info->wall_distance[raycast->ray_ct] = raycast->minor_distance;
}

/**
 * @brief We swap the x position to fix the mirror effect that ocurrs when display
 * a texture
 *
 * @param raycast Struct containing all raycaster previously calculated values
 *
 * @return Void
 */
static inline void invert_texture_x(t_raycast *raycast)
{
	if (raycast->horizontal_dist <= raycast->vertical_dist)
	{
		if (raycast->ray_angle < PI)
			raycast->texture_x_hp = 1.0f - raycast->texture_x_hp;
	}
	else
	{
		if (raycast->ray_angle > RAD_90_DEG && raycast->ray_angle < RAD_270_DEG)
			raycast->texture_x_hp = 1.0f - raycast->texture_x_hp;
	}
}
/**
 * @brief Where all the graphic magic takes place here we will calculate ray
 * col gross and draw a pixel col of each colum color per gross.
 *
 * @param game_wrap Struct containing game most important information
 * @param raycast Struct containing all raycaster previously calculated values
 *
 * @return Void
 */
static inline void draw_frame_cols(t_game *game_wrap, t_raycast *raycast)
{
	raycast->wall_len = (CUBSIZE * game_wrap->game_view->height) / raycast->minor_distance;
	raycast->save_tex_y = 0;
	raycast->texture_steps = (float)CUBSIZE / raycast->wall_len;
	if (raycast->wall_len > game_wrap->game_view->height)
	{
		raycast->save_tex_y = ((raycast->wall_len - game_wrap->game_view->height) / 2) * raycast->texture_steps;
		raycast->wall_len = game_wrap->game_view->height;
	}
	raycast->wall_start = (game_wrap->game_view->height - raycast->wall_len) / 2;
	raycast->iter_gross = 0;
	invert_texture_x(raycast);
	while (raycast->iter_gross < game_wrap->col_gross)
	{
		raycast->texture_y_hp = raycast->save_tex_y;
		draw_player_view_line(game_wrap, raycast, (uint32_t)(raycast->ray_ct * game_wrap->col_gross) + raycast->iter_gross);
		raycast->iter_gross++;
	}
}

/**
 * @brief The raycaster itself. Here we calculate what player sees,
 * the player view field is 60º,and we create rays on that player view field
 * and calculate where they hit to display a vertical wall.
 *
 * @note Needs to be sliced and optimized
 * @note This documentation will be updated
 * @note How palyer will see something that is too far away?
 *
 * @param game_wrap Represents the structure that contains all map content
 * and info needed
 * @param player_info Represents the strcuture that contains all
 * player info needed
 *
 * @return Void
 */
void draw_rays(t_game *game_wrap, t_player *player_info)
{
	t_raycast raycast;

	init_raycast_values(player_info, &raycast);
	raycast.ray_angle = player_info->ang - (ONE_DEGREE * HALF_FOV);
	check_angle_bounds(&raycast.ray_angle);
	while (raycast.ray_ct < game_wrap->pixels_cols)
	{
		check_horizontal_ray(game_wrap, &raycast);
		check_vertical_ray(game_wrap, &raycast);
		check_minor_distance(&raycast);
		raycast.texture_x_hp -= floor(raycast.texture_x_hp);
		fix_fish_eye(player_info, &raycast);
		draw_frame_cols(game_wrap, &raycast);
		draw_line_simple(game_wrap, (float[]){game_wrap->map_view->width / 2, game_wrap->map_view->height / 2}, (float[]){(raycast.ray_x / CUBSIZE) * game_wrap->tile_size - game_wrap->offset_x, (raycast.ray_y / CUBSIZE) * game_wrap->tile_size - game_wrap->offset_y}, RAY_COLOR);
		raycast.ray_angle += ((ONE_DEGREE * FOV) / game_wrap->pixels_cols);
		check_angle_bounds(&raycast.ray_angle);
		raycast.ray_ct++;
	}
	draw_sprites(game_wrap, player_info);
}

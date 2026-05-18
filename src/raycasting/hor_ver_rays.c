/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hor_ver_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:08:37 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/13 17:15:35 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline void	inclement_ray_len(t_raycast *rc)
{
	rc->ray_x += rc->ray_x_offset;
	rc->ray_y += rc->ray_y_offset;
	rc->distance_of_field += 1;
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
static inline void	check_distance_of_field(t_game *game_wrap, t_raycast *rc,
		uint8_t mode)
{
	t_coll_tex	aux;

	aux = WALL_TEX;
	while (rc->distance_of_field < FOG)
	{
		rc->map_x = (int)(rc->ray_x) >> game_wrap->const_values.bit_shift;
		rc->map_y = (int)(rc->ray_y) >> game_wrap->const_values.bit_shift;
		if ((rc->map_x >= 0 && rc->map_x < game_wrap->map_width)
			&& (rc->map_y >= 0 && rc->map_y < game_wrap->map_height)
			&& ((game_wrap->map[rc->map_y][rc->map_x] == '1')
			|| game_wrap->map[rc->map_y][rc->map_x] == 'P'))
		{
			rc->distance_of_field = FOG;
			aux = WALL_TEX;
			if (game_wrap->map[rc->map_y][rc->map_x] == 'P')
				aux = DOOR_TEX;
		}
		else
			inclement_ray_len(rc);
	}
	if (!mode)
		rc->coll_tex_hor = aux;
	else
		rc->coll_tex_ver = aux;
}

static inline void	edge_angle_case_and_final_values(t_game *game_wrap,
		t_raycast *rc, int mode)
{
	if (rc->ray_angle == 0 || rc->ray_angle == PI)
	{
		rc->ray_x = rc->player_posx_cube;
		rc->ray_y = rc->player_posy_cube;
		rc->distance_of_field = FOG;
	}
	if (!mode)
	{
		check_distance_of_field(game_wrap, rc, mode);
		rc->horizontal_dist = dist(rc->player_posx_cube, rc->player_posy_cube,
				rc->ray_x, rc->ray_y);
		rc->horizontal_x = rc->ray_x;
		rc->horizontal_y = rc->ray_y;
	}
	else
	{
		check_distance_of_field(game_wrap, rc, mode);
		rc->vertical_dist = dist(rc->player_posx_cube, rc->player_posy_cube,
				rc->ray_x, rc->ray_y);
		rc->vertical_x = rc->ray_x;
		rc->vertical_y = rc->ray_y;
	}
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
void	check_horizontal_ray(t_game *game_wrap, t_raycast *rc)
{
	t_const_vals const_val;

	const_val = game_wrap->const_values;
	rc->distance_of_field = 0;
	if (tan(rc->ray_angle) == 0)
		rc->ray_angle += 0.0001f;
	rc->arc_tan = -1 / tan(rc->ray_angle);
	if (rc->ray_angle > PI)
	{
		rc->ray_y = (((int)rc->player_posy_cube >> const_val.bit_shift) << const_val.bit_shift)
			- 0.01f;
		rc->ray_x = (rc->player_posy_cube - rc->ray_y) * rc->arc_tan
			+ rc->player_posx_cube;
		rc->ray_y_offset = -1 * CUBSIZE;
		rc->ray_x_offset = -1 * rc->ray_y_offset * rc->arc_tan;
	}
	if (rc->ray_angle < PI)
	{
		rc->ray_y = (((int)rc->player_posy_cube >> const_val.bit_shift) << const_val.bit_shift)
			+ CUBSIZE;
		rc->ray_x = (rc->player_posy_cube - rc->ray_y) * rc->arc_tan
			+ rc->player_posx_cube;
		rc->ray_y_offset = CUBSIZE;
		rc->ray_x_offset = -1 * rc->ray_y_offset * rc->arc_tan;
	}
	edge_angle_case_and_final_values(game_wrap, rc, 0);
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
void	check_vertical_ray(t_game *game_wrap, t_raycast *rc)
{
	t_const_vals const_val;

	const_val =game_wrap->const_values;
	rc->distance_of_field = 0;
	if (tan(rc->ray_angle) == 0)
		rc->ray_angle += 0.00001;
	rc->neg_tan = -1 * tan(rc->ray_angle);
	if (rc->ray_angle > const_val.rad_90_deg && rc->ray_angle < const_val.rad_270_deg)
	{
		rc->ray_x = (((int)rc->player_posx_cube >> const_val.bit_shift) << const_val.bit_shift)
			- 0.01f;
		rc->ray_y = (rc->player_posx_cube - rc->ray_x) * rc->neg_tan
			+ rc->player_posy_cube;
		rc->ray_x_offset = -CUBSIZE;
		rc->ray_y_offset = -rc->ray_x_offset * rc->neg_tan;
	}
	if (rc->ray_angle < const_val.rad_90_deg || rc->ray_angle > const_val.rad_270_deg)
	{
		rc->ray_x = (((int)rc->player_posx_cube >> const_val.bit_shift) << const_val.bit_shift)
			+ CUBSIZE;
		rc->ray_y = (rc->player_posx_cube - rc->ray_x) * rc->neg_tan
			+ rc->player_posy_cube;
		rc->ray_x_offset = CUBSIZE;
		rc->ray_y_offset = -rc->ray_x_offset * rc->neg_tan;
	}
	edge_angle_case_and_final_values(game_wrap, rc, 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:08:28 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/11 19:08:31 by jose-ara         ###   ########.fr       */
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
inline float	dist(float x0, float y0, float x1, float y1)
{
	return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

/**
 * @brief Here we check if the angle passed as a parameter has got out of bounds
 *
 * @param angle The angle to be check
 *
 * @return Void
 */
inline void	check_angle_bounds(float *angle)
{
	if (*angle < 0)
		*angle += RAD_360_DEG;
	else if (*angle > RAD_360_DEG)
		*angle -= RAD_360_DEG;
}

/**
 * @brief Having horizontal and vertical ray lengths computed we check which
 * one is the minor one, which will be the one to be drawed.
 *
 * @param raycast Struct containing all raycaster previously calculated values
 *
 * @return Void
 */
inline void	check_minor_distance(t_raycast *raycast)
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
inline void	fix_fish_eye(t_player *player_info, t_raycast *raycast)
{
	raycast->corrected_angle = player_info->ang - raycast->ray_angle;
	check_angle_bounds(&raycast->corrected_angle);
	raycast->minor_distance = raycast->minor_distance
		* cos(raycast->corrected_angle);
	player_info->wall_distance[raycast->ray_ct] = raycast->minor_distance;
}

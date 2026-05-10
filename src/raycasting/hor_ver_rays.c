#include "../../include/cub3d.h"

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
void check_horizontal_ray(t_game *game_wrap, t_raycast *rc)
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
void check_vertical_ray(t_game *game_wrap, t_raycast *rc)
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

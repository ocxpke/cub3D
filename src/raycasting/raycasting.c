#include "../../include/cub3d.h"

/**
 * @brief We calculate the distance from point (x0, y0) to point (x1, y1). Pythagorean theorem
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

static inline void init_raycast_values(t_player *player_info, t_raycast *raycast)
{
	raycast->player_angle = player_info->ang;
	raycast->player_posX_cube = player_info->posX * CUBSIZE;
	raycast->player_posY_cube = player_info->posY * CUBSIZE;
	raycast->player_posX_map = player_info->posX;
	raycast->player_posY_map = player_info->posY;
	raycast->horizontal_dist = 100000;
	raycast->vertical_dist = 100000;
	raycast->ray_ct = 0;
	raycast->ray_x = 0;
	raycast->ray_y = 0;
	raycast->ray_x_offset = 0;
	raycast->ray_y_offset = 0;
	raycast->ceil_frame = (get_time() / 150) % CEILING_NUMBER;
	raycast->floor_frame = (get_time() / 150) % FLOOR_NUMBER;
}

static inline void check_distance_of_field(t_game *game_wrap, t_raycast *rc)
{
	while (rc->distance_of_field < FOG)
	{
		rc->map_x = (int)(rc->ray_x) >> BIT_SHIFT;
		rc->map_y = (int)(rc->ray_y) >> BIT_SHIFT;
		if ((rc->map_x >= 0 && rc->map_x < game_wrap->map_width) && (rc->map_y >= 0 && rc->map_y < game_wrap->map_height) && (game_wrap->map[rc->map_y][rc->map_x] == '1'))
			rc->distance_of_field = FOG;
		else
		{
			rc->ray_x += rc->ray_x_offset;
			rc->ray_y += rc->ray_y_offset;
			rc->distance_of_field += 1;
		}
	}
}

static inline void check_horizontal_ray(t_game *game_wrap, t_raycast *rc)
{
	rc->distance_of_field = 0;
	if (rc->ray_angle == 0)
		rc->ray_angle += 0.00001;
	rc->arc_tan = -1 / tan(rc->ray_angle);
	if (rc->ray_angle > PI)
	{
		rc->ray_y = (((int)rc->player_posY_cube >> BIT_SHIFT) << BIT_SHIFT) - 0.0001;
		rc->ray_x = (rc->player_posY_cube - rc->ray_y) * rc->arc_tan + rc->player_posX_cube;
		rc->ray_y_offset = -CUBSIZE;
		rc->ray_x_offset = -rc->ray_y_offset * rc->arc_tan;
	}
	if (rc->ray_angle < PI)
	{
		rc->ray_y = (((int)rc->player_posY_cube >> BIT_SHIFT) << BIT_SHIFT) + CUBSIZE;
		rc->ray_x = (rc->player_posY_cube - rc->ray_y) * rc->arc_tan + rc->player_posX_cube;
		rc->ray_y_offset = CUBSIZE;
		rc->ray_x_offset = -rc->ray_y_offset * rc->arc_tan;
	}
	check_distance_of_field(game_wrap, rc);
	rc->horizontal_dist = dist(rc->player_posX_cube, rc->player_posY_cube, rc->ray_x, rc->ray_y);
	rc->horizontal_x = rc->ray_x;
	rc->horizontal_y = rc->ray_y;
}

static inline void check_vertical_ray(t_game *game_wrap, t_raycast *rc)
{
	rc->distance_of_field = 0;
	if (rc->ray_angle == 0)
		rc->ray_angle += 0.00001;
	rc->neg_tan = -1 * tan(rc->ray_angle);
	if (rc->ray_angle > RAD_90_DEG && rc->ray_angle < RAD_270_DEG)
	{
		rc->ray_x = (((int)rc->player_posX_cube >> BIT_SHIFT) << BIT_SHIFT) - 0.0001;
		rc->ray_y = (rc->player_posX_cube - rc->ray_x) * rc->neg_tan + rc->player_posY_cube;
		rc->ray_x_offset = -CUBSIZE;
		rc->ray_y_offset = -rc->ray_x_offset * rc->neg_tan;
	}
	if (rc->ray_angle < RAD_90_DEG || rc->ray_angle > RAD_270_DEG)
	{
		rc->ray_x = (((int)rc->player_posX_cube >> BIT_SHIFT) << BIT_SHIFT) + CUBSIZE;
		rc->ray_y = (rc->player_posX_cube - rc->ray_x) * rc->neg_tan + rc->player_posY_cube;
		rc->ray_x_offset = CUBSIZE;
		rc->ray_y_offset = -rc->ray_x_offset * rc->neg_tan;
	}
	check_distance_of_field(game_wrap, rc);
	rc->vertical_dist = dist(rc->player_posX_cube, rc->player_posY_cube, rc->ray_x, rc->ray_y);
	rc->vertical_x = rc->ray_x;
	rc->vertical_y = rc->ray_y;
}

static inline void check_minor_distance(t_raycast *raycast)
{
	if (raycast->horizontal_dist <= raycast->vertical_dist)
	{
		raycast->ray_x = raycast->horizontal_x;
		raycast->ray_y = raycast->horizontal_y;
		raycast->minor_distance = raycast->horizontal_dist;
		raycast->hor_ver = 1;
		raycast->texture_x_hp = raycast->ray_x / CUBSIZE;
	}
	else
	{
		raycast->ray_x = raycast->vertical_x;
		raycast->ray_y = raycast->vertical_y;
		raycast->minor_distance = raycast->vertical_dist;
		raycast->hor_ver = -1;
		raycast->texture_x_hp = raycast->ray_y / CUBSIZE;
	}
}

static inline void fix_fish_eye(t_player *player_info, t_raycast *raycast)
{
	raycast->corrected_angle = player_info->ang - raycast->ray_angle;
	check_angle_bounds(&raycast->corrected_angle);
	raycast->minor_distance = raycast->minor_distance * cos(raycast->corrected_angle);
}

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
	raycast->iterGross = 0;
	while (raycast->iterGross < game_wrap->col_gross)
	{
		raycast->texture_y_hp = raycast->save_tex_y;
		draw_player_view_line(game_wrap, raycast, (uint32_t)(raycast->ray_ct * game_wrap->col_gross) + raycast->iterGross);
		raycast->iterGross++;
	}
}

/**
 * @brief The raycaster itself. Here we calculate what player sees, the player view field is
 * 60º, and we create rays on that player view field and calculate where they hit to display a vertical wall.
 *
 * @note Needs to be sliced and optimized
 * @note This documentation will be updated
 * @note How palyer will see something that is too far away?
 *
 * @param game_wrap Represents the structure that contains all map content and info needed
 * @param player_info Represents the strcuture that contains all player info needed
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
		draw_line_simple(game_wrap, (float[]){player_info->posX * MAP_CUB_SIZE, player_info->posY * MAP_CUB_SIZE},
						 (float[]){(raycast.ray_x / CUBSIZE) * MAP_CUB_SIZE, (raycast.ray_y / CUBSIZE) * MAP_CUB_SIZE}, 0x00FF00FF);
		raycast.ray_angle += ((ONE_DEGREE * FOV) / game_wrap->pixels_cols);
		check_angle_bounds(&raycast.ray_angle);
		raycast.ray_ct++;
	}
}

#include "../../include/cub3d.h"

/**
 * @note No la documento por q esto va a cambiar
 */
// arreglar esta mierda
void draw_line_simple(t_game *game, float p0[2], float p1[2], uint32_t color)
{
	float dx = p1[0] - p0[0]; // x1 - x0;
	float dy = p1[1] - p0[1];

	float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

	// 1. PROTECCIÓN: Evitamos la división por cero si es un solo punto
	if (steps == 0)
		steps = 1;

	float x_inc = dx / steps;
	float y_inc = dy / steps;

	float current_x = p0[0];
	float current_y = p0[1];

	// Bucle para pintar
	for (int i = 0; i <= steps; i++)
	{
		// 3. PRECISIÓN: Redondeamos en lugar de truncar
		int pixel_x = (int)roundf(current_x);
		int pixel_y = (int)roundf(current_y);

		// Comprobación de límites (una sola vez)
		if (pixel_x >= 0 && (uint32_t)pixel_x < game->map_view->width &&
			pixel_y >= 0 && (uint32_t)pixel_y < game->map_view->height)
		{
			mlx_put_pixel(game->map_view, pixel_x, pixel_y, color);
		}

		current_x += x_inc;
		current_y += y_inc;
	}
}

uint32_t get_color_from_texture(mlx_texture_t *texture, uint16_t x, uint16_t y, float dist)
{
	/**
	 * @note ver mejor lo de la intensidad
	 */
	float dist_ratio = dist / MAX_PLAYER_VIEW_DIST;
	if (dist_ratio > 1.0f)
		dist_ratio = 1.0f;
	float intensity = 0.9f - (dist_ratio * 0.8f);
	if (dist >= MAX_PLAYER_VIEW_DIST)
		intensity = 0;
	if (x >= texture->width || y >= texture->height)
		return (0);
	uint32_t base = (x + (y * texture->width)) * 4;
	uint8_t valR = texture->pixels[base] * intensity;
	uint8_t valG = texture->pixels[base + 1] * intensity;
	uint8_t valB = texture->pixels[base + 2] * intensity;
	uint32_t finalColor = valR << 24 | valG << 16 | valB << 8 | 0xFF;
	return (finalColor);
}

static inline mlx_texture_t *get_wall_texture(t_game *game, t_raycast *rc)
{
	if (rc->hor_ver == 1)
	{
		if (rc->ray_angle > RAD_180_DEG && rc->ray_angle < RAD_360_DEG)
			return (game->wall_text.south_tex);
		else
			return (game->wall_text.north_tex);
	}
	else
	{
		if (rc->ray_angle > RAD_90_DEG && rc->ray_angle < RAD_270_DEG)
			return (game->wall_text.east_tex);
		else
			return (game->wall_text.west_tex);
	}
}

void draw_ceil_floor(t_game *game_wrap, t_raycast *rc, uint32_t x_trunc, int pixel, int mode)
{
	t_raycast_ceil_fl *rc_fl_cl;
	uint32_t color_text;

	rc_fl_cl = &(rc->ceil_fl_vars);
	if (mode)
		rc_fl_cl->ceil_fl_dy = (game_wrap->game_view->height / 2.0f) - pixel;
	else
		rc_fl_cl->ceil_fl_dy = pixel - (game_wrap->game_view->height / 2.0f);
	if (rc_fl_cl->ceil_fl_dy <= 0.0f)
		rc_fl_cl->ceil_fl_dy = 1.0f;

	// Obtenemos la distancia total del jugador al pixel a representar y arreglamos de esa distacia el ojo de pez
	rc_fl_cl->ceil_fl_straight_dist = (game_wrap->game_view->height / 2.0f) / rc_fl_cl->ceil_fl_dy;
	if (rc_fl_cl->cos_corrected < 0.0001f)
		rc_fl_cl->cos_corrected = 0.0001f;
	rc_fl_cl->ceil_fl_true_dist = rc_fl_cl->ceil_fl_straight_dist / rc_fl_cl->cos_corrected;

	// Obtenemos la posicion del pixel del suelo a dibujar en el mapa (el suelo hace de mapa en si mismo)
	rc_fl_cl->ceil_fl_world_x = rc->player_posX_map + (rc_fl_cl->cos_ray * rc_fl_cl->ceil_fl_true_dist);
	// Se pone un mas por que el eje Y avanza hacia abajo
	rc_fl_cl->ceil_fl_world_y = rc->player_posY_map + (rc_fl_cl->sin_ray * rc_fl_cl->ceil_fl_true_dist);

	// Transoformamos los valores del mapa de suelo a valores para poder obtener los x, y de las texturas
	// rc_fl_cl->ceil_fl_tex_x = (uint16_t)(rc_fl_cl->ceil_fl_world_x * CUBSIZE) % CUBSIZE;
	// rc_fl_cl->ceil_fl_tex_y = (uint16_t)(rc_fl_cl->ceil_fl_world_y * CUBSIZE) % CUBSIZE;

	float wx = fmodf(rc_fl_cl->ceil_fl_world_x, 1.0f);
	if (wx < 0)
		wx += 1.0f;
	float wy = fmodf(rc_fl_cl->ceil_fl_world_y, 1.0f);
	if (wy < 0)
		wy += 1.0f;
	rc_fl_cl->ceil_fl_tex_x = (uint16_t)(wx * CUBSIZE) % CUBSIZE;
	rc_fl_cl->ceil_fl_tex_y = (uint16_t)(wy * CUBSIZE) % CUBSIZE;

	// Dibujamos la textura
	if (mode)
		color_text = get_color_from_texture(game_wrap->ceiling_tex.all_textures[rc->ceil_frame],
											rc_fl_cl->ceil_fl_tex_x, rc_fl_cl->ceil_fl_tex_y, 0);
	else
		color_text = get_color_from_texture(game_wrap->floor_tex.all_textures[rc->floor_frame],
											rc_fl_cl->ceil_fl_tex_x, rc_fl_cl->ceil_fl_tex_y, 0);
	mlx_put_pixel(game_wrap->game_view, x_trunc, pixel, color_text);
}

void draw_player_view_line(t_game *game_wrap, t_raycast *rc, uint32_t x_trunc)
{
	uint32_t color_text;
	uint32_t y0_trunc = (uint32_t)rc->wall_start;
	uint32_t y1_trunc = (uint32_t)rc->wall_start + rc->wall_len;
	uint16_t wall_hit_x = (uint16_t)(CUBSIZE * rc->texture_x_hp);
	if (rc->ns_ew == -1)
		wall_hit_x = CUBSIZE - 1 - wall_hit_x;
	// incializamos valores del dibujado suelo/techo
	// Arreglamos el fisheye obteniendo el angulo a dibujar del suelo
	rc->ceil_fl_vars.ceil_fl_ang = rc->player_angle - rc->ray_angle;
	check_angle_bounds(&(rc->ceil_fl_vars.ceil_fl_ang));
	rc->ceil_fl_vars.cos_corrected = cos(rc->ceil_fl_vars.ceil_fl_ang);
	rc->ceil_fl_vars.cos_ray = cos(rc->ray_angle);
	rc->ceil_fl_vars.sin_ray = sin(rc->ray_angle);
	for (uint32_t i = 0; i < game_wrap->game_view->height; i++)
	{
		if ((i >= y0_trunc) && (i <= y1_trunc))
		{
			color_text = get_color_from_texture(get_wall_texture(game_wrap, rc),
												wall_hit_x, (uint16_t)rc->texture_y_hp, rc->minor_distance);
			mlx_put_pixel(game_wrap->game_view, x_trunc, i, color_text);
			rc->texture_y_hp += rc->texture_steps;
		}
		else if (i < y0_trunc)
			mlx_put_pixel(game_wrap->game_view, x_trunc, i, game_wrap->ceiling_tex.color); // draw_ceil_floor(game_wrap, rc, x_trunc, i, 1);
		else
			draw_ceil_floor(game_wrap, rc, x_trunc, i, 0);
	}
}

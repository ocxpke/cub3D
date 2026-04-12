#include "../../include/cub3d.h"

/**
 * @note No la documento por q esto va a cambiar
 */
// arreglar esta mierda
void draw_line_simple(t_game *game, float x0, float y0, float x1, float y1)
{
	float dx = x1 - x0;
	float dy = y1 - y0;

	float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

	// 1. PROTECCIÓN: Evitamos la división por cero si es un solo punto
	if (steps == 0)
		steps = 1;

	float x_inc = dx / steps;
	float y_inc = dy / steps;

	float current_x = x0;
	float current_y = y0;

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
			mlx_put_pixel(game->map_view, pixel_x, pixel_y, game->line_color);
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

void draw_player_view_line(t_game *game, t_raycast *rc, uint32_t x_trunc)
{
	uint32_t y0_trunc = (uint32_t)rc->wall_start;
	uint32_t y1_trunc = (uint32_t)rc->wall_start + rc->wall_len;
	uint16_t wall_hit_x = (uint16_t)(CUBSIZE * rc->texture_x_hp);
	if (rc->ns_ew == -1)
		wall_hit_x = CUBSIZE - 1 - wall_hit_x;
	for (uint32_t i = 0; i < game->game_view->height; i++)
	{
		if ((i >= y0_trunc) && (i <= y1_trunc))
		{
			uint32_t color_text = get_color_from_texture(game->wall_text.south_tex,
														 wall_hit_x, (uint16_t)rc->texture_y_hp, rc->minor_distance);
			mlx_put_pixel(game->game_view, x_trunc, i, color_text);
			rc->texture_y_hp += rc->texture_steps;
		}
		else if (i < y0_trunc)
			mlx_put_pixel(game->game_view, x_trunc, i, 0x4682B4FF);
		else
			mlx_put_pixel(game->game_view, x_trunc, i, 0x228B22FF);
	}
}

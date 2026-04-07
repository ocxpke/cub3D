#include "../../include/cub3d.h"

/**
 * @note No la documento por q esto va a cambiar
 */
// arreglar esta mierda
void draw_line_simple(t_game *game, float x0, float y0, float x1, float y1, uint32_t color, int mode)
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

	// 2. OPTIMIZACIÓN: Elegimos el "view" destino una sola vez fuera del bucle
	// Asumo que map_view y game_view son de tipo mlx_image_t* (MLX42) o similar
	void *target_view; // Cambia 'void *' por 'mlx_image_t *' o tu struct de imagen
	int max_width, max_height;

	if (!mode)
	{
		target_view = game->map_view;
		max_width = game->map_view->width;
		max_height = game->map_view->height;
	}
	else
	{
		target_view = game->game_view;
		max_width = game->game_view->width;
		max_height = game->game_view->height;
	}

	// Bucle para pintar
	for (int i = 0; i <= steps; i++)
	{
		// 3. PRECISIÓN: Redondeamos en lugar de truncar
		int pixel_x = (int)roundf(current_x);
		int pixel_y = (int)roundf(current_y);

		// Comprobación de límites (una sola vez)
		if (pixel_x >= 0 && pixel_x < max_width &&
			pixel_y >= 0 && pixel_y < max_height)
		{
			mlx_put_pixel(target_view, pixel_x, pixel_y, color);
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
	uint32_t base = (x + (y * texture->width)) * 4;
	uint8_t valR = texture->pixels[base] * intensity;
	uint8_t valG = texture->pixels[base + 1] * intensity;
	uint8_t valB = texture->pixels[base + 2] * intensity;
	uint32_t finalColor = valR << 24 | valG << 16 | valB << 8 | 0xFF;
	return (finalColor);
}

void draw_player_view_line(t_game *game, t_player *player_info, t_raycast *rc, uint32_t x_trunc)
{
	uint32_t y0_trunc = (uint32_t)rc->wall_start;
	uint32_t y1_trunc = (uint32_t)rc->wall_start + rc->wall_len;
	uint16_t wall_hit_x = (uint16_t)(CUBSIZE * rc->texture_x_hp);
	(void)player_info;
	if (rc->ns_ew == -1)
		wall_hit_x = CUBSIZE - 1 - wall_hit_x;
	for (uint32_t i = 0; i < game->game_view->height; i++)
	{
		if ((i >= y0_trunc) && (i <= y1_trunc))
		{
			uint32_t color_text = get_color_from_texture(game->wall_text.south_tex, wall_hit_x, rc->texture_y_hp, rc->minor_distance);
			mlx_put_pixel(game->game_view, x_trunc, i, color_text);
			rc->texture_y_hp += rc->texture_steps;
		}
		else if (i < y0_trunc)
			mlx_put_pixel(game->game_view, x_trunc, i, 0x4682B4FF);
		else
			mlx_put_pixel(game->game_view, x_trunc, i, 0x228B22FF);
	}
}

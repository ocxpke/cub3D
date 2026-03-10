#include "../../include/cub3d.h"

// arreglar esta mierda
void draw_line_simple(t_game *game, float x0, float y0, float x1, float y1, uint32_t color, int mode)
{
	// 1. Calculamos la diferencia entre los puntos
	float dx = x1 - x0;
	float dy = y1 - y0;

	// 2. ¿Qué lado es más largo? Ese será nuestro número total de "pasos" a pintar
	float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

	// 3. Calculamos cuánto hay que avanzar en X y en Y por cada paso
	float x_inc = dx / steps;
	float y_inc = dy / steps;

	// Empezamos en el punto de origen
	float current_x = x0;
	float current_y = y0;

	// 4. Bucle simple: pintamos y avanzamos hasta llegar a los 'pasos' totales
	for (int i = 0; i <= steps; i++)
	{
		// Protección para no salirnos de la ventana (Segfault)

		if (!mode)
		{
			if (current_x >= 0 && current_x < game->map_view->width &&
				current_y >= 0 && current_y < game->map_view->height)
			{
				mlx_put_pixel(game->map_view, (int)current_x, (int)current_y, color);
			}
		}
		else
		{
			if (current_x >= 0 && current_x < game->game_view->width &&
				current_y >= 0 && current_y < game->game_view->height)
			{
				mlx_put_pixel(game->game_view, (int)current_x, (int)current_y, color);
			}
		}

		// Avanzamos un pasito hacia el destino
		current_x += x_inc;
		current_y += y_inc;
	}
}

#include "../../include/cub3d.h"

// --- Variables de tu Sprite ---
int total_frames = 4;	 // Si tu carrusel tiene 4 imágenes
int frame_width = 64;	 // Cada imagen mide 64 píxeles de ancho
int anim_speed_ms = 150; // Cambiar de imagen cada 150 milisegundos (Ajusta a tu gusto)

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
static inline void check_angle_bounds(float *angle)
{
	if (*angle < 0)
		*angle += PI_360_DEG;
	else if (*angle > PI_360_DEG)
		*angle -= PI_360_DEG;
}

static inline void init_raycast_values(t_game *game_wrap, t_player *player_info, t_raycast *raycast)
{
	raycast->player_posX = player_info->posX * CUBSIZE;
	raycast->player_posY = player_info->posY * CUBSIZE;
	raycast->horizontal_distance = 100000;
	raycast->vertical_distance = 100000;
	raycast->col_gross = game_wrap->game_view->width / game_wrap->pixels_cols;
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
	int r = 0, mx = 0, my = 0, dof = 0;
	float rx = 0, ry = 0, ra = 0, xo = 0, yo = 0;
	float playerX = player_info->posX * CUBSIZE, playerY = player_info->posY * CUBSIZE;
	float distV = 1000000, distH = 1000000;
	float vx = 0, vy = 0, hx = 0, hy = 0;
	float distT;
	int rayGross = game_wrap->game_view->width / game_wrap->pixels_cols;
	float wallHitPoint = 0;

	(void) raycast;//borrar
	// Esto hay que mirarlo
	float horizon = game_wrap->game_view->height / 2.0f;
	// ¡Adiós a la tangente en el suelo! Usamos la misma constante implícita de tus muros.
	float planeDist = (float)game_wrap->game_view->height;
	float playerHeight = CUBSIZE / 2.0f;

	ra = player_info->ang - (ONE_DEGREE * HALF_FOV);
	check_angle_bounds(&ra);

	for (r = 0; r < game_wrap->pixels_cols; r++)
	{
		// --- Cálculo Mágico ---
		long long current_time = get_time();

		// Al dividir el tiempo total entre la velocidad, sabemos cuántos fotogramas han pasado desde que se encendió el PC.
		// Usando el módulo (% total_frames), lo mantenemos dando vueltas (0, 1, 2, 3, 0, 1, 2, 3...)
		int current_frame = (current_time / anim_speed_ms) % total_frames;
		// horizontal
		dof = 0;

		// How tan(ra) can be 0?
		float aTan = -1 / tan(ra);

		if (ra < PI)
		{
			ry = (((int)playerY >> BIT_SHIFT) << BIT_SHIFT) + CUBSIZE;
			rx = (playerY - ry) * aTan + playerX;
			yo = CUBSIZE;
			xo = -yo * aTan;
		}
		if (ra > PI)
		{
			ry = (((int)playerY >> BIT_SHIFT) << BIT_SHIFT) - 0.0001;
			rx = (playerY - ry) * aTan + playerX;
			yo = -1 * CUBSIZE;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = playerX;
			ry = playerY;
			dof = FOG;
		}

		while (dof < FOG)
		{
			mx = (int)(rx) >> BIT_SHIFT;
			my = (int)(ry) >> BIT_SHIFT;
			if ((mx >= 0 && mx < game_wrap->map_width) && (my >= 0 && my < game_wrap->map_height) && (game_wrap->map[my][mx] == '1'))
				dof = FOG;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		distH = dist(playerX, playerY, rx, ry);
		hx = rx;
		hy = ry;

		// Vertical
		dof = 0;
		float nTan = -tan(ra);

		if (ra < PI_90_DEG || ra > PI_270_DEG)
		{
			rx = (((int)playerX >> BIT_SHIFT) << BIT_SHIFT) + CUBSIZE;
			ry = (playerX - rx) * nTan + playerY;
			xo = CUBSIZE;
			yo = -xo * nTan;
		}
		if (ra > PI_90_DEG && ra < PI_270_DEG)
		{
			rx = (((int)playerX >> BIT_SHIFT) << BIT_SHIFT) - 0.0001;
			ry = (playerX - rx) * nTan + playerY;
			xo = -1 * CUBSIZE;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = playerX;
			ry = playerY;
			dof = FOG;
		}

		while (dof < FOG)
		{
			mx = (int)(rx) >> BIT_SHIFT;
			my = (int)(ry) >> BIT_SHIFT;
			if ((mx >= 0 && mx < game_wrap->map_width) && (my >= 0 && my < game_wrap->map_height) && (game_wrap->map[my][mx] == '1'))
				dof = FOG;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		distV = dist(playerX, playerY, rx, ry);
		vx = rx;
		vy = ry;

		if (distH <= distV)
		{
			rx = hx;
			ry = hy;
			distT = distH;
			wallHitPoint = rx / CUBSIZE;
		}
		else
		{
			rx = vx;
			ry = vy;
			distT = distV;
			wallHitPoint = ry / CUBSIZE;
		}
		wallHitPoint -= floor(wallHitPoint);
		/**
		 * @todo VER MEJOR COMO TRATAR EL OJO DE PEZ
		 */
		float ca = player_info->ang - ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		distT = distT * cos(ca);

		float lineH = (CUBSIZE * game_wrap->game_view->height) / distT;

		float wallHitPixel = 0;
		float steps = (float)game_wrap->texture->height / lineH;
		if (lineH > game_wrap->game_view->height)
		{
			wallHitPixel = ((lineH - game_wrap->game_view->height) / 2) * steps;
			lineH = game_wrap->game_view->height;
		}
		float lineO = (game_wrap->game_view->height - lineH) / 2;
		for (int i = 0; i < rayGross; i++)
		{
			if (distH <= distV)
				draw_player_view_line(game_wrap, player_info, (rayGross * r) + i, lineO, lineH + lineO, wallHitPoint, wallHitPixel, steps, distH);
			else
				draw_player_view_line(game_wrap, player_info, (rayGross * r) + i, lineO, lineH + lineO, wallHitPoint, wallHitPixel, steps, distV);
		}

		// ESTO SE REHARA ENTERO (LA FUNCION DE DIBUJAR SUELO)

		// --- DENTRO del bucle de rayos (donde ya tienes el resto) ---
		float ca_fix = player_info->ang - ra;
		check_angle_bounds(&ca_fix);
		float raFix = cos(ca_fix); // ✅ sin ONE_DEGREE

		float cos_ra = cos(ra); // ✅ ra ya en radianes
		float sin_ra = sin(ra);

		for (uint32_t y = (uint32_t)(lineO + lineH); y < game_wrap->game_view->height; y++)
		{
			float dy = y - horizon;
			if (dy == 0)
				dy = 1; // Seguridad total

			// Distancia real en Píxeles del Mundo
			float rowDistance = (planeDist * playerHeight) / dy / raFix;

			// 2. USAMOS playerX y playerY (que ya están multiplicados por CUBSIZE)
			float tx = playerX + cos_ra * rowDistance;
			float ty = playerY + sin_ra * rowDistance;

			// 3. Ya NO multiplicamos por CUBSIZE aquí, las coordenadas ya son reales
			int tex_x = (int)tx & (game_wrap->texture->width - 1);
			int tex_y = (int)ty & (game_wrap->texture->height - 1);

			uint32_t color = get_color_from_texture(game_wrap->t1[current_frame], tex_x, tex_y, 0);

			for (int i = 0; i < rayGross; i++)
			{
				uint32_t screen_x = (r * rayGross) + i;
				if (screen_x < game_wrap->game_view->width)
					mlx_put_pixel(game_wrap->game_view, screen_x, y, color);
			}
		}
		draw_line_simple(game_wrap, player_info->posX * MAP_CUB_SIZE, player_info->posY * MAP_CUB_SIZE, (rx / CUBSIZE) * MAP_CUB_SIZE, (ry / CUBSIZE) * MAP_CUB_SIZE, 0x00FF00FF, 0);
		ra += ((ONE_DEGREE * FOV) / game_wrap->pixels_cols);
		check_angle_bounds(&ra);
	}
}

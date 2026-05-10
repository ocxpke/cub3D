#include "../../include/cub3d.h"

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

			if (color != IGNORE_COLOR)
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

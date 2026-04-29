#include "../../include/cub3d.h"

/**
 * @brief Esat funcion pilla el area DE DISPLAY donde de verdad podemos dibujar, no la ventana entera, no la pantalla entera,
 * el espacio REAL USABLE, no hay otra forma de cogerlo
 *
 * @note Ya use esta funcion, espero que no me de problemas ahora
 *
 * @param game_wrap Represents the structure that contains all map content and info needed
 */
static int create_window(t_game *game_wrap)
{
	int width;
	int height;
	GLFWwindow *windowGLFW;
	mlx_t *window;

	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	mlx_set_setting(MLX_MAXIMIZED, 1);
	window = mlx_init(750, 750, "cub3d", true);
	if (!window)
		return (perror("Error creating window"), 1);
	game_wrap->window = window;
	windowGLFW = (GLFWwindow *)game_wrap->window->window;
	glfwGetFramebufferSize(windowGLFW, &width, &height);
	game_wrap->init_width = (uint32_t)width;
	game_wrap->init_height = (uint32_t)height;
	ft_printf("Resolución real de trabajo: %u x %u\n",
			  game_wrap->init_width, game_wrap->init_height);
	return (0);
}

static int load_map_textures(t_wall_textures *wall_tex, t_dpar *game_d)
{
	wall_tex->type = IMAGE_TEXTURE;
	wall_tex->north_tex = mlx_load_png(game_d->map_s->tex_col_s->no_tex_path);
	if (!wall_tex->north_tex)
		return (perror("Error opening north map texture"), 1);
	wall_tex->south_tex = mlx_load_png(game_d->map_s->tex_col_s->so_tex_path);
	if (!wall_tex->south_tex)
		return (perror("Error opening south map texture"), 1);
	wall_tex->east_tex = mlx_load_png(game_d->map_s->tex_col_s->ea_tex_path);
	if (!wall_tex->east_tex)
		return (perror("Error opening map texture"), 1);
	wall_tex->west_tex = mlx_load_png(game_d->map_s->tex_col_s->we_tex_path);
	if (!wall_tex->west_tex)
		return (perror("Error opening map texture"), 1);
	return (0);
}

static void set_ceil_floor_texture(t_game *game_wrap, t_tex_col *colors_info)
{
	game_wrap->ceiling_tex.type = COLOR_TEXTURE;
	game_wrap->ceiling_tex.color = get_color_from_struct(colors_info->cl_col_val, 0xFF);
	if (game_wrap->ceiling_tex.color == COLOR_SWAP)
		check_ceiling_texture(&(game_wrap->ceiling_tex));
	game_wrap->floor_tex.type = COLOR_TEXTURE;
	game_wrap->floor_tex.color = get_color_from_struct(colors_info->fl_col_val, 0xFF);
	if (game_wrap->floor_tex.color == COLOR_SWAP)
		check_floor_texture(&(game_wrap->floor_tex));
}

int manage_mlx42_resources(t_game *game_wrap, t_dpar *game_d)
{
	if (create_window(game_wrap))
		return (1);
	game_wrap->game_view = mlx_new_image(game_wrap->window, game_wrap->init_width, game_wrap->init_height);
	if (!game_wrap->game_view || (mlx_image_to_window(game_wrap->window, game_wrap->game_view, 0, 0) < 0))
		return (perror("Error allocating game image"), 1);
	game_wrap->map_view = mlx_new_image(game_wrap->window, MAP_CUB_SIZE * game_wrap->map_width, MAP_CUB_SIZE * game_wrap->map_height);
	if (!game_wrap->map_view || (mlx_image_to_window(game_wrap->window, game_wrap->map_view, game_wrap->game_view->width - game_wrap->map_view->width, 0) < 0))
		return (perror("Error allocating map image"), 1);
	printf("MAP_CUBE IS %d AND POS IS %d\n", MAP_CUB_SIZE * game_wrap->map_width, game_wrap->game_view->width - game_wrap->map_view->width);
	if (load_map_textures(&game_wrap->wall_text, game_d))
		return (1);
	game_wrap->col_gross = game_wrap->game_view->width / (FOV * PIX_COL);
	if (game_wrap->col_gross < 1)
		game_wrap->col_gross = 1;
	game_wrap->pixels_cols = game_wrap->game_view->width / game_wrap->col_gross;
	set_ceil_floor_texture(game_wrap, game_d->map_s->tex_col_s);
	mlx_set_cursor_mode(game_wrap->window, MLX_MOUSE_HIDDEN);
	return (0);
}

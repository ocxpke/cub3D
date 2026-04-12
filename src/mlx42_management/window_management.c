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

// static int load_floor_textures(t_ceil_floor_tex *ceiling_tex)
// {
// 	game_wrap->t1[0] = mlx_load_png("./src/imgs/LavaF1.png");
// 	if (!game_wrap->t1[0])
// 		return (perror("Error opening floor texture"), 1);
// 	game_wrap->t1[1] = mlx_load_png("./src/imgs/LavaF2.png");
// 	if (!game_wrap->t1[1])
// 		return (perror("Error opening floor texture"), 1);
// 	game_wrap->t1[2] = mlx_load_png("./src/imgs/LavaF3.png");
// 	if (!game_wrap->t1[2])
// 		return (perror("Error opening floor texture"), 1);
// 	game_wrap->t1[3] = mlx_load_png("./src/imgs/LavaF4.png");
// 	if (!game_wrap->t1[3])
// 		return (perror("Error opening floor texture"), 1);
// }

static int load_map_textures(t_wall_textures *wall_tex /*, t_ceil_floor_tex *ceiling_tex, t_ceil_floor_tex *floor_tex*/)
{
	wall_tex->type = IMAGE_TEXTURE;
	wall_tex->north_tex = mlx_load_png("./src/imgs/s_north.png");
	if (!wall_tex->north_tex)
		return (perror("Error opening north map texture"), 1);
	wall_tex->south_tex = mlx_load_png("./src/imgs/s_south.png");
	if (!wall_tex->south_tex)
		return (perror("Error opening south map texture"), 1);
	wall_tex->east_tex = mlx_load_png("./src/imgs/s_east.png");
	if (!wall_tex->east_tex)
		return (perror("Error opening map texture"), 1);
	wall_tex->west_tex = mlx_load_png("./src/imgs/s_west.png");
	if (!wall_tex->west_tex)
		return (perror("Error opening map texture"), 1);
	return (0);
}

int manage_mlx42_resources(t_game *game_wrap)
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
	if (load_map_textures(&game_wrap->wall_text))
		return (1);
	game_wrap->pixels_cols = FOV * PIX_COL;
	if ((FOV * PIX_COL) > game_wrap->game_view->width)
		game_wrap->pixels_cols = game_wrap->game_view->width;
	return (0);
}

#include "../../include/cub3d.h"

/**
 * @brief Esat funcion pilla el area DE DISPLAY donde de verdad podemos dibujar, no la ventana entera, no la pantalla entera,
 * el espacio REAL USABLE, no hay otra forma de cogerlo
 *
 * @note Ya use esta funcion, espero que no me de problemas ahora
 *
 * @param game_wrap Represents the structure that contains all map content and info needed
 */
static inline void create_window(t_game *game_wrap)
{
	// static inline vs inline static???
	int width;
	int height;
	GLFWwindow *windowGLFW;
	mlx_t *window;

	// 1-> Forzamos a que la ventana se cree maximizada para ocupar el workarea
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	mlx_set_setting(MLX_MAXIMIZED, 1);
	window = mlx_init(1, 1, "cub3d", true);
	if (!window)
		return (perror("Error creating window"));
	game_wrap->window = window;

	// 3-> Obtenemos el puntero de la ventana de GLFW
	windowGLFW = (GLFWwindow *)game_wrap->window->window;

	glfwGetFramebufferSize(windowGLFW, &width, &height);

	game_wrap->init_width = (uint32_t)width;
	game_wrap->init_height = (uint32_t)height;

	ft_printf("Resolución real de trabajo: %u x %u\n",
			  game_wrap->init_width, game_wrap->init_height);
}

int manage_mlx42_resources(t_game *game_wrap)
{
	mlx_image_t *game_view;
	mlx_image_t *map_view;

	create_window(game_wrap);
	game_view = mlx_new_image(game_wrap->window, game_wrap->init_width, game_wrap->init_height);
	if (!game_view || (mlx_image_to_window(game_wrap->window, game_view, 0, 0) < 0))
		exit(EXIT_FAILURE);
	game_wrap->game_view = game_view;
	map_view = mlx_new_image(game_wrap->window, MAP_CUB_SIZE * game_wrap->map_width, MAP_CUB_SIZE * game_wrap->map_height);
	if (!map_view || (mlx_image_to_window(game_wrap->window, map_view, game_view->width - map_view->width, 0) < 0))
		exit(EXIT_FAILURE);
	game_wrap->map_view = map_view;
	printf("MAP_CUBE IS %d AND POS IS %d\n", MAP_CUB_SIZE * game_wrap->map_width, game_view->width - map_view->width);
	game_wrap->texture = mlx_load_png("./src/raccoonPIX.png");
	if (!game_wrap->texture)
		perror("Fallo imagen");
	return 0;
}

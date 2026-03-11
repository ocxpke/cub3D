#include "../../include/cub3d.h"
# include <GLFW/glfw3.h>

/**
 * @brief Esat funcion pilla el area DE DISPLAY donde de verdad podemos dibujar, no la ventana entera, no la pantalla entera,
 * el espacio REAL USABLE, no hay otra forma de cogerlo
 *
 * @note Ya use esta funcion, espero que no me de problemas ahora
 *
* @param game_wrap Represents the structure that contains all map content and info needed
 */
inline void	take_window_data(t_game *game_wrap)
{
	GLFWmonitor	*monitor;

	monitor = glfwGetPrimaryMonitor();
	if (!monitor)
		return (perror("Error monitor"), exit(EXIT_FAILURE));
	glfwGetMonitorWorkarea(monitor, NULL, NULL, &(game_wrap->init_width),
		&(game_wrap->init_heigth));
	ft_printf("Width: %d, Height: %d\n", game_wrap->init_width,
		game_wrap->init_heigth);
}

#include "../../include/cub3d.h"

/**
 * @brief We take the color values from
 *
 * @param color Struct cotaining the Red, Green, and Blue values
 * @param alpha The corresponding alpha value, for opacity
 *
 * @return The color in the corresponding uint32_t
 */
inline void set_color_from_var(t_color *color, uint32_t color_setted)
{
	color->red = (color_setted >> 24) & 0xFF;
	color->green = (color_setted >> 16) & 0xFF;
	color->blue = (color_setted >> 8) & 0xFF;
	color->alpha = color_setted & 0xFF;
}

/**
 * @brief We take the color from the struct and set an uint32_t value
 * that we can use later
 *
 * @param color Struct cotaining the Red, Green, and Blue values
 * @param alpha The corresponding alpha value, for opacity
 *
 * @return The color in the corresponding uint32_t
 */
inline uint32_t get_color_from_struct(t_color *color, uint8_t alpha)
{
	uint32_t ret_color;

	ret_color = ((uint32_t)color->red << 24);
	ret_color |= ((uint32_t)color->green << 16);
	ret_color |= ((uint32_t)color->blue << 8);
	ret_color |= ((uint32_t)alpha);
	return (ret_color);
}

#include "../../include/cub3d.h"
/**
 * @note This function is used to concat the file number + extension
 *
 * @param i The number itself
 *
 * @return The pointer to the start of the string.
 */
static char *num_and_extension(int i)
{
	char *ret;
	char *num_text;

	num_text = ft_itoa(i);
	if (!num_text)
		exit(EXIT_FAILURE);
	ret = ft_calloc(1, ft_strlen(num_text) + ft_strlen(".png") + 1);
	if (!ret)
		exit(EXIT_FAILURE);
	ft_strlcat(ret, num_text, ft_strlen(num_text) + ft_strlen(".png") + 1);
	ft_strlcat(ret, ".png", ft_strlen(num_text) + ft_strlen(".png") + 1);
	free(num_text);
	return (ret);
}

static void load_all_frame_textures(t_ceil_floor_tex *ceil_floor_tex, char *image_path, int limit)
{
	int i;
	char *num_ext;
	i = 1;
	while (i <= limit)
	{
		num_ext = num_and_extension(i);
		ft_strlcat(image_path, num_ext, ft_strlen(image_path) + ft_strlen(num_ext) + 1);
		// printf("%s\n", image_path);
		ceil_floor_tex->all_textures[i - 1] = mlx_load_png(image_path);
		printf("%d --> %p\n", i - 1, ceil_floor_tex->all_textures[i - 1]);
		if (!ceil_floor_tex->all_textures[i - 1])
			return (perror("fail on image"), exit(EXIT_FAILURE));
		ft_memset(&image_path[ft_strlen(image_path) - ft_strlen(num_ext)], 0, ft_strlen(num_ext) - 1);
		free(num_ext);
		i++;
	}
}

void check_ceiling_texture(t_ceil_floor_tex *ceil_floor_tex)
{
	char *image_path;
	char *num_text;

	if (ceil_floor_tex->color == COLOR_SWAP)
		return;
	num_text = ft_itoa(CEILING_NUMBER);
	if (!num_text)
		exit(EXIT_FAILURE);
	image_path = ft_calloc(1, ft_strlen(CEILING_PATH) + ft_strlen(CEILING_TEXTURE) + ft_strlen(num_text) + ft_strlen(".png") + 1);
	if (!image_path)
		exit(EXIT_FAILURE);
	free(num_text);
	ft_strlcat(image_path, CEILING_PATH, ft_strlen(image_path) + ft_strlen(CEILING_PATH) + 1);
	ft_strlcat(image_path, CEILING_TEXTURE, ft_strlen(image_path) + ft_strlen(CEILING_TEXTURE) + 1);
	ceil_floor_tex->all_textures = ft_calloc(CEILING_NUMBER, sizeof(mlx_texture_t *));
	if (!ceil_floor_tex->all_textures)
		exit(EXIT_FAILURE);
	load_all_frame_textures(ceil_floor_tex, image_path, CEILING_NUMBER);
	/**
	 * Vaya bug de mierda como uso el puntero de num_text pero este no se pasa por referencia se
	 * liberaba 2 veces la misma posicion de memoria.
	 */
	free(image_path);
}

void check_floor_texture(t_ceil_floor_tex *ceil_floor_tex)
{
	char *image_path;
	char *num_text;

	if (ceil_floor_tex->color == COLOR_SWAP)
		return;
	num_text = ft_itoa(FLOOR_NUMBER);
	if (!num_text)
		exit(EXIT_FAILURE);
	image_path = ft_calloc(1, ft_strlen(FLOOR_PATH) + ft_strlen(FLOOR_TEXTURE) + ft_strlen(num_text) + ft_strlen(".png") + 1);
	if (!image_path)
		exit(EXIT_FAILURE);
	free(num_text);
	ft_strlcat(image_path, FLOOR_PATH, ft_strlen(image_path) + ft_strlen(FLOOR_PATH) + 1);
	ft_strlcat(image_path, FLOOR_TEXTURE, ft_strlen(image_path) + ft_strlen(FLOOR_TEXTURE) + 1);
	ceil_floor_tex->all_textures = ft_calloc(FLOOR_NUMBER, sizeof(mlx_texture_t *));
	if (!ceil_floor_tex->all_textures)
		exit(EXIT_FAILURE);
	load_all_frame_textures(ceil_floor_tex, image_path, FLOOR_NUMBER);
	free(image_path);
}

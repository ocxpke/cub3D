/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_frames.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:24:43 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/03 15:24:44 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @note This function is used to concat the file number + extension
 *
 * @param i The number itself
 *
 * @return The pointer to the start of the string.
 */
char	*num_and_extension(int i, const char* ext)
{
	char	*ret;
	char	*num_text;

	num_text = ft_itoa(i);
	if (!num_text)
		exit(EXIT_FAILURE);
	ret = ft_calloc(1, ft_strlen(num_text) + ft_strlen(ext) + 1);
	if (!ret)
		exit(EXIT_FAILURE);
	ft_strlcat(ret, num_text, ft_strlen(num_text) + ft_strlen(ext) + 1);
	ft_strlcat(ret, ext, ft_strlen(num_text) + ft_strlen(ext) + 1);
	free(num_text);
	return (ret);
}

static void	load_all_frame_textures(t_ceil_floor_tex *ceil_floor_tex,
		char *image_path, int limit)
{
	int		i;
	char	*num_ext;

	i = 1;
	while (i <= limit)
	{
		num_ext = num_and_extension(i, TEXTURE_EXT);
		ft_strlcat(image_path, num_ext, ft_strlen(image_path)
			+ ft_strlen(num_ext) + 1);
		ceil_floor_tex->all_textures[i - 1] = mlx_load_png(image_path);
		if (!ceil_floor_tex->all_textures[i - 1])
			return (perror("fail on image"), exit(EXIT_FAILURE));
		ft_memset(&image_path[ft_strlen(image_path) - ft_strlen(num_ext)], 0,
			ft_strlen(num_ext) - 1);
		free(num_ext);
		i++;
	}
}

void	check_ceiling_texture(t_ceil_floor_tex *ceil_tex)
{
	char	*image_path;
	char	*num_text;

	if (ceil_tex->color != COLOR_SWAP)
		return ;
	num_text = ft_itoa(CEILING_TEX_NUMBER);
	if (!num_text)
		exit(EXIT_FAILURE);
	image_path = ft_calloc(1, ft_strlen(CEILING_PATH)
			+ ft_strlen(CEILING_TEXTURE) + ft_strlen(num_text)
			+ ft_strlen(TEXTURE_EXT) + 1);
	if (!image_path)
		exit(EXIT_FAILURE);
	free(num_text);
	ft_strlcat(image_path, CEILING_PATH, ft_strlen(image_path)
		+ ft_strlen(CEILING_PATH) + 1);
	ft_strlcat(image_path, CEILING_TEXTURE, ft_strlen(image_path)
		+ ft_strlen(CEILING_TEXTURE) + 1);
	ceil_tex->all_textures = ft_calloc(CEILING_TEX_NUMBER,
			sizeof(mlx_texture_t *));
	if (!ceil_tex->all_textures)
		exit(EXIT_FAILURE);
	load_all_frame_textures(ceil_tex, image_path, CEILING_TEX_NUMBER);
	free(image_path);
	ceil_tex->type = IMAGE_TEXTURE;
}

void	check_floor_texture(t_ceil_floor_tex *floor_tex)
{
	char	*image_path;
	char	*num_text;

	if (floor_tex->color != COLOR_SWAP)
		return ;
	num_text = ft_itoa(FLOOR_TEX_NUMBER);
	if (!num_text)
		exit(EXIT_FAILURE);
	image_path = ft_calloc(1, ft_strlen(FLOOR_PATH) + ft_strlen(FLOOR_TEXTURE)
			+ ft_strlen(num_text) + ft_strlen(TEXTURE_EXT) + 1);
	if (!image_path)
		exit(EXIT_FAILURE);
	free(num_text);
	ft_strlcat(image_path, FLOOR_PATH, ft_strlen(image_path)
		+ ft_strlen(FLOOR_PATH) + 1);
	ft_strlcat(image_path, FLOOR_TEXTURE, ft_strlen(image_path)
		+ ft_strlen(FLOOR_TEXTURE) + 1);
	floor_tex->all_textures = ft_calloc(FLOOR_TEX_NUMBER,
			sizeof(mlx_texture_t *));
	if (!floor_tex->all_textures)
		exit(EXIT_FAILURE);
	load_all_frame_textures(floor_tex, image_path, FLOOR_TEX_NUMBER);
	free(image_path);
	floor_tex->type = IMAGE_TEXTURE;
}

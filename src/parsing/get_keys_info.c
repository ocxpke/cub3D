/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_keys_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:54:42 by romorale          #+#    #+#             */
/*   Updated: 2026/05/12 18:32:24 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	get_key_pos(int x, int y, t_pairs *key_arr, int k)
{
	key_arr->k_num = k + 1;
	key_arr->k_posx = x;
	key_arr->k_posy = y;
}

void	search_loop(t_dpar *game, char **map)
{
	int	j;
	int	i;
	int	k;
	int	k_len;

	j = -1;
	i = -1;
	k = 0;
	k_len = game->map_s->key_count - 1;
	while (map[++j])
	{
		i = 0;
		while (map[j][++i])
		{
			if (map[j][i] == 'K')
			{
				if (k <= k_len)
				{
					get_key_pos(j, i, &game->map_s->keys_arr[k], k);
				}
				k++;
			}
		}
	}
}

void	find_keys(t_dpar *game, char **map)
{
	int		i;
	t_pairs	*k_arr;

	i = 1;
	k_arr = malloc(sizeof(t_pairs) * (game->map_s->key_count));
	if (!(game->map_s->keys_arr))
		free(game->map_s->keys_arr);
	game->map_s->keys_arr = k_arr;
	if (map && game->map_s->keys_arr)
		search_loop(game, map);
}

void	print_key_positions(t_dpar *game)
{
	int	k;

	k = 0;
	if (game->map_s->key_count == 0)
	{
		printf(H_B"No Keys found in map!\n");
		return ;
	}
	while (k < game->map_s->key_count)
	{
		printf(H_Y"Key"H_B" number: "MAG"["
			H_B"%d"MAG"]\n"RES, game->map_s->keys_arr[k].k_num);
		printf(H_B"pos x:      "MAG"["
			H_B"%d"MAG"]\n"RES, game->map_s->keys_arr[k].k_posx);
		printf(H_B"pos y:      "MAG"["
			H_B"%d"MAG"]\n"RES, game->map_s->keys_arr[k].k_posy);
		printf(MAG"---------------------------------------------------\n");
		k++;
	}
}

void	get_keys_info(t_dpar *game)
{
	int	key_num;

	key_num = game->map_s->key_count;
	if (key_num > 0)
	{
		find_keys(game, game->map_s->map);
	}
}

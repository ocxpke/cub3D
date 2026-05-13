/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_key_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:34:16 by romorale          #+#    #+#             */
/*   Updated: 2026/05/12 18:55:53 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_key_array(t_dpar *path)
{
	int	k_num;

	k_num = path->map_s->key_count;
	if (k_num > 0)
		free(path->map_s->keys_arr);
}

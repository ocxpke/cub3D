/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:53:05 by romorale          #+#    #+#             */
/*   Updated: 2026/04/06 15:24:41 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	valid_map_content(t_dpar *game)
{
	if (!valid_content(game))
		return (0);
	else
	{
		printf(B_G"YAY!"GRN" All character used in the map are valid!!!\n"RES);
		return (1);
	}
}

int	valid_map_structure(t_dpar *game)
{
	if (!valid_structure(game))
		return (0);
	else
	{
		printf(B_G"YAY!"GRN" The map structure is valid!!!\n"RES);
		return (1);
	}
}

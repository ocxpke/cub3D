/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:31:30 by romorale          #+#    #+#             */
/*   Updated: 2026/05/13 14:57:38 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parsing_part_1(int ac, char **av, t_dpar *game)
{
	if (ac != 2 || !check_arg(av[1]))
	{
		printf(B_R"Error:"RED" Missing file or invalid file extension!\n"RES);
		exit(0);
	}
	printf(B_G"YAY!"GRN" Valid file extension!!!\n"RES);
	game->file_cont = get_file(av[1]);
	if (!game->file_cont)
	{
		printf(B_R"Error:"RED" File does not exist!\n"RES);
		exit(0);
	}
	printf(B_G"YAY!"GRN" File opened successfully!!!\n"RES);
	if (!check_empty_file(game))
	{
		printf(B_R"Error:"RED" File is empty!\n"RES);
		free_file_cont(game);
		exit(0);
	}
	if (!check_for_anything_else(game))
	{
		printf(B_R"Error:"RED" File contains something unidentifiable!\n"RES);
		free_file_cont(game);
		exit(0);
	}
}

void	parsing_part_2(t_dpar *game)
{
	if (!file_checklist(game))
	{
		printf(B_R"Error:"RED" Missing, mislabled or "RES);
		printf(RED"invalid number of elements!\n"RES);
		free_up_to_cheklist(game);
		exit(0);
	}
	printf(B_G"YAY!"GRN" Valid number of elements!!!\n"RES);
	if (!map_placement(game))
	{
		printf(B_R"Error:"RED" Missing or misplaced map!\n"RES);
		free_up_to_cheklist(game);
		exit(0);
	}
	printf(B_G"YAY!"GRN" Valid map placement!!!\n"RES);
	if (!get_elements(game))
	{
		printf(B_R"Error:"RED" Unable to retrieve elements!\n"RES);
		free_up_to_cheklist(game);
		exit(0);
	}
	printf(B_G"YAY!"GRN" Elements retrieved successfully!!!\n"RES);
}

void	parsing_part_3(t_dpar *game)
{
	if (!validate_and_clean_elements(game))
	{
		free_map(game);
		free_up_to_cheklist(game);
		exit(0);
	}
	printf(B_G"YAY!"GRN" Elements are valid!!!\n"RES);
	if (!valid_map_content(game))
	{
		free_map(game);
		free_up_to_cheklist(game);
		exit(0);
	}
	if (!valid_map_structure(game))
	{
		free_map(game);
		free_up_to_cheklist(game);
		exit(0);
	}
}

int	parsing(int ac, char **av, t_dpar *game)
{
	parsing_part_1(ac, av, game);
	struct_init(game);
	parsing_part_2(game);
	parsing_part_3(game);
	open_and_check_textures(game);
	get_map_info(game);
	square_map(game);
	get_keys_info(game);
	print_mapfile(game);
	printf(H_Y"\n__________________DONE_PARSING!___________________\n\n"RES);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_end.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:26:56 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/11 19:26:57 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_END_H
# define INIT_END_H
# include "cub3d.h"

void	set_init_vals(t_game *game_wrap, t_player *player_info, t_dpar *game_d);
void	macro_checker(void);
void	exit_mlx42(t_game *game_wrap, t_player *player_info, t_dpar *game_d);

#endif

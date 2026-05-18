/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:26:44 by jose-ara          #+#    #+#             */
/*   Updated: 2026/05/18 16:06:36 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUX_H
# define AUX_H
# include "cub3d.h"

void		set_color_from_var(t_color *color, uint32_t color_setted);
uint32_t	get_color_from_struct(t_color *color, uint8_t alpha);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:34:16 by romorale          #+#    #+#             */
/*   Updated: 2026/04/21 20:03:04 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
///break this stuff down

void	checklist_init(t_dpar *path)
{
	path->checklist_s = malloc(sizeof(t_checklist) * 1);
	if (!(path->checklist_s))
		free(path->checklist_s);
	path->checklist_s->no_tex = 0;
	path->checklist_s->so_tex = 0;
	path->checklist_s->we_tex = 0;
	path->checklist_s->ea_tex = 0;
	path->checklist_s->fl_col = 0;
	path->checklist_s->cl_col = 0;
	path->checklist_s->ok = 0;
}

void	tex_col_val_init(t_dpar *path)
{
	path->map_s->tex_col_s->fl_col_val = malloc(sizeof(t_color) * 1);
	if (!(path->map_s->tex_col_s->fl_col_val))
		free(path->map_s->tex_col_s->fl_col_val);
	path->map_s->tex_col_s->fl_col_val->red = 0;
	path->map_s->tex_col_s->fl_col_val->green = 0;
	path->map_s->tex_col_s->fl_col_val->blue = 0;
	path->map_s->tex_col_s->cl_col_val = malloc(sizeof(t_color) * 1);
	if (!(path->map_s->tex_col_s->cl_col_val))
		free(path->map_s->tex_col_s->cl_col_val);
	path->map_s->tex_col_s->cl_col_val->red = 0;
	path->map_s->tex_col_s->cl_col_val->green = 0;
	path->map_s->tex_col_s->cl_col_val->blue = 0;
}

void	tex_col_init(t_dpar *path)
{
	path->map_s->tex_col_s = malloc(sizeof(t_tex_col) * 1);
	if (!(path->map_s->tex_col_s))
		free(path->map_s->tex_col_s);
	path->map_s->tex_col_s->no_tex = 0;
	path->map_s->tex_col_s->so_tex = 0;
	path->map_s->tex_col_s->we_tex = 0;
	path->map_s->tex_col_s->ea_tex = 0;
	path->map_s->tex_col_s->no_tex_path = 0;
	path->map_s->tex_col_s->so_tex_path = 0;
	path->map_s->tex_col_s->we_tex_path = 0;
	path->map_s->tex_col_s->ea_tex_path = 0;
	path->map_s->tex_col_s->fl_col = 0;
	path->map_s->tex_col_s->cl_col = 0;
}

void	struct_init(t_dpar *path)
{
	path->map_s = malloc(sizeof(t_map) * 1);
	if (!(path->map_s))
		free(path->map_s);
	path->map_s->key_count = 0;
	path->map_s->door_count = 0;
	tex_col_init(path);
	tex_col_val_init(path);
	checklist_init(path);
}

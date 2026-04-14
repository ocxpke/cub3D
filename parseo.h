/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romorale <romorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 20:57:13 by romorale          #+#    #+#             */
/*   Updated: 2026/04/13 16:40:36 by romorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../Libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

//text colors for visabilily
//no color
# define RES "\033[0m"

//regular
# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

//high intensty
# define HBLK "\e[0;90m"
# define H_R "\e[0;91m"
# define H_G "\e[0;92m"
# define H_Y "\e[0;93m"
# define H_B "\e[0;94m"
# define H_M "\e[0;95m"
# define H_C "\e[0;96m"
# define H_W "\e[0;97m"

//bold
# define B_N "\033[1;30m"
# define B_R "\033[1;31m"
# define B_G "\033[1;32m"
# define B_Y "\033[1;33m"
# define B_B "\033[1;34m"
# define B_M "\033[1;35m"
# define B_C "\033[1;36m"
# define B_W "\033[1;37m"

//Bold high intensity text
# define BHBLK "\e[1;90m"
# define BHRED "\e[1;91m"
# define BHGRN "\e[1;92m"
# define BHYEL "\e[1;93m"
# define BHBLU "\e[1;94m"
# define BHMAG "\e[1;95m"
# define BHCYN "\e[1;96m"
# define BHWHT "\e[1;97m"

//High intensty background 
# define BLKHB "\e[0;100m"
# define REDHB "\e[0;101m"
# define GRNHB "\e[0;102m"
# define YELHB "\e[0;103m"
# define BLUHB "\e[0;104m"
# define MAGHB "\e[0;105m"
# define CYNHB "\e[0;106m"
# define WHTHB "\e[0;107m"

typedef struct s_color
{
	int		red;
	int		green;
	int		blue;
}		t_color;

typedef struct s_checklist
{
	int		no_tex;
	int		so_tex;
	int		we_tex;
	int		ea_tex;
	int		fl_col;
	int		cl_col;
	int		ok;
}		t_checklist;

typedef struct s_tex_col
{
	char	*no_tex;
	char	*no_tex_path;
	char	*so_tex;
	char	*so_tex_path;
	char	*we_tex;
	char	*we_tex_path;
	char	*ea_tex;
	char	*ea_tex_path;
	char	*fl_col;
	t_color	*fl_col_val;
	char	*cl_col;
	t_color	*cl_col_val;
}		t_tex_col;

typedef struct s_map
{
	char		**map;
	int			rows;
	int			cols;
	int			pstart_x;
	int			pstart_y;
	char		pstart_orientation;
	t_tex_col	*tex_col_s;
}		t_map;

typedef struct s_data
{
//  void		*mlx_ptr;
//	void		*win_ptr;
	t_map		*map_s;
//	t_player	*player_s;
	t_checklist	*checklist_s;
	//t_ray		*ray_s;
	int			fd;
	char		**file_cont;
}		t_data;

//parsing
int		parsing(int ac, char **av, t_data *game);
int		check_arg(char	*str);
char	**get_file(char *av);
char	**split_file(char *s, char c);
int		check_empty_file(t_data *game);
int		check_for_anything_else(t_data *game);
void	struct_init(t_data *path);
int		file_checklist(t_data *game);
int		get_elements(t_data *game);
int		map_placement(t_data *game);
void	elements_placement(t_data *game);
int		map_char(char c);
int		validate_and_clean_elements(t_data *game);
int		get_textures(t_data *game, t_tex_col *tex_col_s);
int		get_f_c(t_data *game, t_tex_col *tex_col_s);
int		find_map(t_data *g);
int		get_map_h(char **map);
int		check_path_ext(char *line);
int		valid_textures(t_data *game);
int		check_textures(t_data *game);
int		valid_f_c(t_data *game);
void	get_color_val_fl(t_data *game, char *line);
void	get_color_val_cl(t_data *game, char *line);
int		check_rgb(t_data	*game);
int		valid_map(t_data *game);
int		valid_map_content(t_data *game);
int		valid_content(t_data *game);
int		valid_map_structure(t_data *game);
int		valid_structure(t_data *game);
int		val_inside_c(char c);
int		check_inner_chars(t_data *game);
void	open_and_check_textures(t_data *game);
void	get_map_info(t_data *game);
int		get_player_pos_col(char **map);
int		get_player_pos_row(char **map);
char	get_orientation(char **map);
int		get_cols(char **map);
int		get_rows(char **map);

//free
void	free_all(t_data *path);
void	free_map(t_data *path);
void	free_file_cont(t_data *path);
void	free_up_to_cheklist(t_data *path);
void	free_tex_col_val(t_data *path);
void	free_tex_col_paths(t_data *path);

//map visualizer
void	print_mapfile( t_data *game);
void	print_mapfile_content( t_data *game);
void	print_mapfile_tex( t_data *game);
void	print_mapfile_colors( t_data *game);
void	print_mapfile_map( t_data *g);
void	print_mapfile_map_info( t_data *game);

#endif
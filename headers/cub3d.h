/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 23:36:49 by mwubneh           #+#    #+#             */
/*   Updated: 2023/11/06 20:41:51 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

////////////////////////////////////////////////////////////////////////////////
//////////                         INCLUDES                           //////////
////////////////////////////////////////////////////////////////////////////////
# include "../minilibx/mlx.h"
# include "../minilibx/mlx_int.h"
# include "../libft/headers/libft.h"
# include <stdio.h>
# include <errno.h>
# include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
//////////                         DEFINES                            //////////
////////////////////////////////////////////////////////////////////////////////
# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define YELLOW	"\033[0;33m"
# define NC		"\033[0m"
////////////////////////////////////////////////////////////////////////////////
//////////                      ERROR_MESSAGES                        //////////
////////////////////////////////////////////////////////////////////////////////
# define ERROR    "Error\n"
# define USAGE    "Usage : ./cub3D <path/map_file.cub> "
# define NOT_FILE "Invalid file ! (directory)"
# define INV_PATH "Invalid path or file."
# define INV_ELEMENT "Invalid file (element in file)."
# define MALL_ERR "malloc failed, "
# define FILE_READ_ERR "Problem encountered during file reading"
////////////////////////////////////////////////////////////////////////////////
//////////                        STRUCTURES                          //////////
////////////////////////////////////////////////////////////////////////////////

typedef struct s_data
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;

	int		f[3];
	int		c[3];

	char	**map;

	void	*element[6];
}		t_data;

typedef struct s_textures
{
	void			*img;
	int				height;
	int				width;
}					t_textures;

typedef struct s_vec
{
	double x;
	double y;
}					t_vec;

typedef struct s_ray
{
	double	inter[2];
	double	dist;
	bool	hit;
}	t_ray;

typedef struct s_player
{
	double	pos[2];
	double	mov[2];
	double	angle_mov;
	double	angle;
	float	fov;
	t_ray	rays[1920];
}			t_player;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win;
	void			*img_ptr;
	int				*addr;
	int				line_length;
	int				bits_per_pixel;
	int				endian;

	t_player		player;
	t_textures		textures[4];
	t_data			*data;
}					t_mlx;

////////////////////////////////////////////////////////////////////////////////
//////////                        PROTOTYPES                          //////////
////////////////////////////////////////////////////////////////////////////////

void	ft_error(char *str, int err);
//--------------------------------get_file.c----------------------------------//
void	get_file(char *path, char ***file);
//-------------------------------data-init.c----------------------------------//
void	data_init(t_data *data, t_mlx *mlx);
//-------------------------------parse_data.c---------------------------------//
void	parse_data(char ***file, t_data *data);
void	get_pos(char **cpy, int start[2]);
//-----------------------------parse_textures.c-------------------------------//
void	parse_textures(char **to_put, char *to_get);
void	is_valid_path(char **path);
char	*trim_end(char *string);
//-----------------------------parse_colors.c-------------------------------//
void	get_colors(int colors[3], char *to_get);
//-----------------------------check_close.c---------------------------------//
bool	is_close(char **cpy);
//-----------------------------expensions.c---------------------------------//
void	zero_expension(char **map, int x, int y);
void	one_expension(char **map, int x, int y);
//-----------------------------check_map.c-----------------------------------//
bool	is_block(char **map);
//-----------------------------check_data.c---------------------------------//
void	check_data(char ***file, t_data *data);
void	free_map(char **cpy);
//-----------------------------map_cpy.c-----------------------------------//
void	map_cpy(char **map, char ***cpy);
//-----------------------------mlx_init.c-----------------------------------//
void	init_mlx(t_mlx *mlx, t_data *data);
int		close_window(t_mlx *mlx);
#endif
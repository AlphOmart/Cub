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
////////////////////////////////////////////////////////////////////////////////
//////////                        PROTOTYPES                          //////////
////////////////////////////////////////////////////////////////////////////////

void	ft_error(char *str, int err);
//--------------------------------get_file.c----------------------------------//
void	get_file(char *path, char ***file);
//-------------------------------data-init.c----------------------------------//
void	data_init(t_data *data);
//-------------------------------parse_data.c---------------------------------//
void	parse_data(char ***file, t_data *data);
//-----------------------------parse_textures.c-------------------------------//
void	parse_textures(char **to_put, char *to_get);
void	is_valid_path(char **path);
char	*trim_end(char *string);
//-----------------------------parse_colors.c-------------------------------//
void	get_colors(int colors[3], char *to_get);
#endif
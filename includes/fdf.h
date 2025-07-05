/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:43:55 by wheino            #+#    #+#             */
/*   Updated: 2025/07/05 21:48:07 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line.h"
# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"
# include <stdio.h> // Printf - testing
# include <fcntl.h> // Read
# include <math.h> //  sin & cos

# define Z_SCALE	0.5
# define WIN_WIDTH	1000
# define WIN_HEIGHT	800
# define ISO_ANGLE	0.52399 // 30 degrees in radians
# define PADDING	100.0

# define OK		0
# define ERROR	-1

// holds the data of a single point.
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}			t_point;

// holds the map data, height, width and all the points.
typedef struct s_map
{
	int		width;
	int		height;
	t_point	**points;
}			t_map;

// holds the MLX state -> MLX pointers (init, window, image, map data, etc.)
typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_data;
	int		bpp;
	int		line_len;
	int		endian;
	t_map	*map;
	int		scale;
	int		x_offset;
	int		y_offset;
}			t_vars;

/* -- test_functions -- */
void	print_map(t_map *map);


/* -- parse_map.c -- */
t_map	*open_and_parse_map(const char *path);
t_map	*parse_map(int fd);
t_map	*init_map_variables(void);
t_list	*read_map_rows(int fd, int *map_width, int *current_height);
t_point	**convert_list_to_2d_points_array(t_list *rows_list, int current_height);

/* -- parse_map_utils.c -- */
int		word_count(char **values);
void	keep_content_free_nodes(t_list **lst);
void	free_nodes_and_content(t_list **lst);
int		free_row_line_values(t_point *row, char *line, char **values);
void	free_map(t_map *map);

/* -- parse_map_row_utils.c -- */
int		check_or_set_width(int *map_width, int line_width);
t_point	*alloc_row(int line_width);
void	fill_row(t_point *row, char **values, int current_height);
int		parse_and_add_row(t_list **rows_list, char *line,
int		current_height, int *map_width);
	
/* -- init_mlx.c -- */
int		init_mlx(t_vars *vars, int width, int height, char *title);

/* -- projection.c -- */
t_point	project_iso(t_point point, t_vars *vars);

/* -- draw_pixel.c -- */
void	put_pixel(t_vars *vars, int x, int y, int color);

/* -- cleanup.c -- */
int		free_and_destroy(t_vars *vars);
	
	#endif
	
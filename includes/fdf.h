/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:43:55 by wheino            #+#    #+#             */
/*   Updated: 2025/07/07 22:33:42 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line.h"
# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h> 

# define Z_SCALE	0.5
# define WIN_WIDTH	2000
# define WIN_HEIGHT	1500
# define ISO_ANGLE	0.52399

# define OK		0
# define ERROR	-1

# define ESC_KEY 65307
# define KEY_UP 65362
# define KEY_DOWN 65364

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}			t_point;

typedef struct s_map
{
	int		width;
	int		height;
	t_point	**points;
}			t_map;

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

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}			t_line;

/* -- parse_map.c -- */
t_map	*open_and_parse_map(const char *path);
t_map	*parse_map(int fd);
t_map	*init_map_variables(void);
t_list	*read_map_rows(int fd, int *map_width, int *current_height);
t_point	**convert_list_to_2d_points_array(t_list *rows_list,
			int current_height);

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
			int current_height, int *map_width);

/* -- init_mlx.c -- */
int		init_mlx(t_vars *vars, int width, int height, char *title);

/* -- projection.c -- */
t_point	project_iso(t_point point, t_vars *vars);

/* -- scale_and_offset.c -- */
void	calculate_scale_and_offset(t_vars *vars);

/* -- draw_pixel.c -- */
void	put_pixel(t_vars *vars, int x, int y, int color);

/* -- draw_line.c -- */
void	draw_line(t_vars *vars, t_point p0, t_point p1, int color);
void	init_line(t_line *line);

/* -- draw_map.c -- */
void	draw_map(t_vars *vars);
void	draw_neighbors(t_vars *vars, int x, int y, t_point current);

/* -- hooks.c -- */
int		handle_keypress(int keycode, t_vars *vars);
int		handle_x_click(t_vars *vars);

/* -- cleanup.c -- */
void	free_and_destroy(t_vars *vars);

#endif
#ifndef FDF_H
# define FDF_H

#include "get_next_line.h"
#include "libft.h"
#include "mlx.h"
#include "stdio.h" // Printf - testing
#include "fcntl.h" // Read
#include "math.h" //  sin & cos

#define Z_SCALE		0.5
#define	WIN_WIDTH 	2500
#define	WIN_HEIGHT	1500
#define ISO_ANGLE	0.52399 // 30 degrees in radians
#define PADDING		100.0

// holds the data of a single point.
typedef struct s_point
{
    int x;
    int y;
    int z;
}   t_point;

// holds the map data, height, width and all the points.
typedef struct s_map
{
    int width;
    int height;
    t_point **points;
}   t_map;

// holds the MLX state -> MLX pointers (init, window, image, map data, etc.)
typedef struct s_vars {
	void	*mlx;
	void	*win;
	void	*img;		// mlx image pointer
	char	*img_data;	// Pointer to image pixel data
	int		bpp;		// bits per pixel
	int		line_len;	// Number of bytes per image line
	int		endian;		// Endianness of the pixel data: 0 means little endian (color bytes stored from least to most significant),
                    	// 1 means big endian (color bytes stored from most to least significant).
                    	// This affects how color values are written into the image buffer.
	int		offset_x;
	int		offset_y;
	double	zoom;
	t_map	*map;
} t_vars;

// holds line algo variables
typedef struct s_line
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;
}	t_line;

/* -- parse_map.c -- */
t_map *parse_map(int fd);
t_map *init_map(void);
int word_count(char **values);
void free_nodes_keep_content(t_list **lst);

/* -- init_mlx.c -- */
int	init_mlx(t_vars *vars, int width, int height, char *title);

/* -- render.c -- */
void	put_pixel(t_vars *vars, int x, int y, int color);
void	init_line(t_line *line, int x0, int y0, int x1, int y1);
void	draw_line(t_vars *vars, int x0, int y0, int x1, int y1, int color);
void	draw_grid(t_vars *vars);

/* -- projection.c -- */
void calculate_offset(t_vars *vars);
void auto_scale_and_center(t_vars *vars);
t_point project_scaled_iso(t_point p, t_vars *vars);
t_point project_iso(t_point p);
t_point project_point(t_point in, t_vars *vars);



#endif

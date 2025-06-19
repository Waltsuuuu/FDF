#ifndef FDF_H
# define FDF_H

#include "get_next_line.h"
#include "libft.h"
#include "mlx.h"
#include <stdio.h> //Printf - testing
#include "fcntl.h" //Read

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
	t_map	*map;
} t_vars;


#endif

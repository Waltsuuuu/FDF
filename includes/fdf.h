#ifndef FDF_H
# define FDF_H

typedef struct s_point
{
    int x;
    int y;
    int z;
}   t_point;

typedef struct s_map
{
    int width;
    int height;
    t_point **points;
}   t_map;


#endif

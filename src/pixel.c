#include "fdf.h"

t_pixel *pixel_new(int x, int y, uint64_t color)
{
	t_pixel *px;
	px = (t_pixel *)ft_g_mmmalloc(sizeof(t_pixel));
	if(px == NULL)
		return NULL;
	px->x = x;
	px->y = y;
	px->color = color;
	return px;
}

t_pixel	*get_pixel(t_pixel ***m, size_t x, size_t y)
{
	return m[y][x];
}

void	scale_pixel(t_pixel *px, double x, double y)
{
	px->x = round(px->x * x);
	px->y = round(px->y * y);
}

void	move_pixel(t_pixel *px, int x, int y)
{
	px->x += x;
	px->y += y;
}

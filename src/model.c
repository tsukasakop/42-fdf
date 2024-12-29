#include "fdf.h"
size_t max_y(t_model *mdl)
{
	return mdl->y_len;
}

size_t max_x(t_model *mdl)
{
	return mdl->x_len;
}

t_point *get_point(t_model *m, size_t x, size_t y)
{
	return &m->p[y][x];
}

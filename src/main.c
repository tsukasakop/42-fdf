//usr/bin/cc $0 -Iinclude -L. -lm -lmlx_Linux -lmlx -lXext -lX11 -o a.out && ./a.out; exit;
//#include <mlx.h>

#include <stdlib.h>
#include <math.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "ft_global.h"
#include "fdf.h"
#include "mlx.h"
#include <stdint.h>
#include <stddef.h>
#include <limits.h>

#include <math.h>

typedef t_pixel*** t_2dmap;

/*
t_point *_point_new()
{
	return ((t_point *)ft_g_mmcalloc(sizeof(t_point)));
}

t_point *point_new(t_model *m, int x, int y)
{
	static *t_point store[MAX_COLLUM][MAX_ROW];

	t_model *m;
	t_point *p;
	if (store[x][y] != NULL)
		return store[x][y];
	m = ft_get_global("model");
	p = _point_new();
	ft_g_mmadd(p);
	if (p == NULL || m == NULL)
		return NULL;
	p->x = x;
	p->y = y;
	p->z = m->t_point[x][y].z;
	p->color = m->t_point[x][y].color;
	return p;
}

double get_top(t_point *p, t_angle *a)
{
	(void)a;
	return p->x + p->y - p->z;
//	double xi;
//	xi = get_x_unit_vector(a)[0];
//	double yi;
//	yi = get_y_unit_vector(a)[0];
//	double zi;
//	zi = get_z_unit_vector(a)[0];
//	return p->x * xi[0] + p->y * yi[0] + p->z * zi[0];
}

double get_left(t_point *p, t_angle *a)
{
	(void)a;
	return p->x - p->y;

//	double xi;
//	xi = get_x_unit_vector(a)[1];
//	double yi;
//	yi = get_y_unit_vector(a)[1];
//	double zi;
//	zi = get_z_unit_vector(a)[1];
//	return p->x * xi[1] + p->y * yi[1] + p->z * zi[1];

}

t_pixel *coord2pixel(t_point *p, t_angle *a)
{
	t_pixel *px;

	px = pixel_new();
	if(px == NULL)
		return NULL;
	px->top = get_top(p, a);
	px->left = get_left(p, a);
	px->color = p->color;
}

t_pixel ***model2pixel(t_angle *a, t_model *m)
{
	int i;
	int j;

	t_pixel *** map;
	map = ft_g_mmcalloc(sizeof(t_pixel **), MAX_ROW);
	if(bn == NULL)
		return NULL;
	ft_g_mmadd((void *)bn);
	i = 0;
	while(i < MAX_ROW)
	{
		j = 0;
		map[i] = ft_g_mmcalloc(sizeof(t_pixel *), MAX_COLUMN);
		while (j < MAX_COLUMN)
		{
			p = coord2pixel(get_point(i, j), a);
			ft_g_mmaddd((void *)p);
			ft_bnadd(bn, (void *)p);
			j++;
		}
		i++;
	}
	return map;
}
*/

int	draw_pixel(t_image *i, t_pixel *p)
{
	size_t c;
	c = (size_t)p->y * i->lsize + (size_t)p->x * (i->bpp / 8);
	if (c / i->bpp * 8 / CANVAS_W >= CANVAS_H)
		return 0;

	//PRINT("Draw point(%d, %d)=%lu\n", p->x, p->y, c);
	//printf("%d, %d\n",p->x, p->y);
	*(t_color *)(((char *)i->addr) + c) = p->color; 
	return 1;
}

int random_img(t_image *i)
{
	int cnt = 0;
	while(cnt++ < 1000)
	{
		int x = random() % CANVAS_H;
		int y = random() % CANVAS_W;
		uint64_t c = (random() % 0x10000000);
		for(int k = 0; k<100;k++)
		{
			for(int j = 0; j<100;j++)
			{
				draw_pixel(i, &((t_pixel){x+k, y+j, c}));
			}
		}
	}
	return 1;
}

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

t_pixel *random_pixel()
{
	t_pixel *px;
	px = pixel_new(random() % CANVAS_H, random() % CANVAS_W, random() % 0x100000000);
	return px;
}

t_pixel *point2pixel(t_point *p)
{
	t_pixel *px;
	int f[2][3] = {
		{90, -110, -1},
		{70, 107, -13}
	};
	px =  pixel_new(
			p->x * f[0][0] + p->y * f[0][1] + p->z * f[0][2],
			p->x * f[1][0] + p->y * f[1][1] + p->z * f[1][2],
			p->color);
	return px;
}

int draw_line(t_image *i, t_pixel *p0, t_pixel *p1)
{
	t_pixel cur;
	t_pixel delta;
	t_pixel slope;
	t_pixel error;

	//PRINT("Drawing line: (%d, %d) to (%d, %d)\n", p0->x, p0->y, p1->x, p1->y);
	cur = (t_pixel){p0->x, p0->y, p0->color};
	delta = (t_pixel) {abs(p1->x - p0->x), abs(p1->y - p0->y), 0x0};
	slope = (t_pixel) {(p0->x < p1->x) * 2 - 1, (p0->y < p1->y) * 2 - 1, 0x0};
	error = (t_pixel) {delta.x - delta.y,0 , 0x0};
	while(cur.x != p1->x || cur.y != p1->y)
	{
		draw_pixel(i, &cur);
		error.y = 2 * error.x;
		if(error.y > -delta.y)
		{
			error.x -= delta.y;
			cur.x += slope.x;
		}
		if(error.y < delta.x)
		{
			error.x += delta.x;
			cur.y += slope.y;
		}
	}
	draw_pixel(i, &cur);
	return 1;
}

t_point *get_point(t_model *m, size_t x, size_t y)
{
	return &m->p[y][x];
}

int draw_random_line(t_image *i)
{
	return draw_line(i, random_pixel(), random_pixel());
}

size_t	get_max_y(t_pixel ***m)
{
	size_t c;

	c = 0;
	while(m[c])
		c++;
	return c;
}

size_t	get_max_x(t_pixel ***m)
{
	size_t c;

	if(m[0] == NULL)
		return 0;
	c = 0;
	while(m[0][c])
		c++;
	return c;
}

t_pixel	*get_pixel(t_pixel ***m, size_t x, size_t y)
{
	return m[y][x];
}

void	set_pixel(t_pixel ***m, size_t x, size_t y, t_pixel *px)
{
	m[y][x] = px;
}

void	draw_wire(t_image *i, t_2dmap map)
{
	PRINT("Drawing wire\n");
	size_t x;
	size_t y;
	size_t max_x;
	size_t max_y;

	y = 0;
	max_x = get_max_x(map);
	max_y = get_max_y(map);
	PRINT("x: %lu, y: %lu\n", max_x, max_y);
	while (y < max_y)
	{
		x = 0;
		while(x < max_x)
		{
			//PRINT("x: %lu, y: %lu\n", x, y);
			if (x < max_x - 1)
				draw_line(i, get_pixel(map, x, y), get_pixel(map, x + 1, y));
			if (y < max_y - 1)
				draw_line(i, get_pixel(map, x, y), get_pixel(map, x, y + 1));
			x++;
		}
		y++;
	}
}

t_pixel	***_map_new(size_t x, size_t y)
{
	PRINT("Making map\n");
	t_pixel ***map;
	map = ft_g_mmmalloc(sizeof(t_pixel **)*(y+1));
	size_t i;
	i=0;
	while(i < y)
	{
		map[i] = ft_g_mmmalloc(sizeof(t_pixel *)*(x+1));
		map[i][x] = NULL;
		i++;
	}
	map[y] = NULL;
	return map;
}

size_t max_y(t_model *mdl)
{
	return mdl->y_len;
}

size_t max_x(t_model *mdl)
{
	return mdl->x_len;
}

void	map_iter(t_pixel ***map, void(*f)(t_pixel *))
{
	size_t x;
	size_t y;
	size_t max_x;
	size_t max_y;

	y = 0;
	max_x = get_max_x(map);
	max_y = get_max_y(map);
	while (y < max_y)
	{
		x = 0;
		while(x < max_x)
		{
			f(get_pixel(map, x, y));
			x++;
		}
		y++;
	}
}

t_pixel	***model_to_2dmap(t_model	*mdl)
{
	t_pixel ***map;
	size_t x;
	size_t y;

	map = _map_new(max_x(mdl), max_y(mdl));
	y = 0;
	while(map[y])
	{
		x = 0;
		while(map[y][x])
		{
			set_pixel(map, x, y, point2pixel(get_point(mdl, x, y)));
			x++;
		}
		y++;
	}
	return map;
}

void	search_limit(t_pixel *px)
{
	t_norm *n;
	n = (t_norm *)ft_get_global("norm");
	if(px->x > n->max[0])
		n->max[0] = px->x;
	if(px->y > n->max[1])
		n->max[1] = px->y;
	if(px->x < n->min[0])
		n->min[0] = px->x;
	if(px->y < n->min[1])
		n->min[1] = px->y;
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

void	norm_pixel(t_pixel *px)
{
	t_norm *n;
	n = (t_norm *)ft_get_global("norm");
	scale_pixel(px, n->scale[0], n->scale[1]); 
	move_pixel(px, n->move[0], n->move[1]); 
}

void	norm_2dmap(t_pixel ***map)
{
	t_norm n;
	n = (t_norm){{INT_MIN, INT_MIN}, {INT_MAX, INT_MAX}, {0.0, 0.0}, {0, 0}};
	ft_set_global("norm", &n);
	map_iter(map, search_limit);
	n.scale[0] = (double)(CANVAS_W - 1) / (n.max[0] - n.min[0]);
	n.scale[1] = (double)(CANVAS_H - 1) / (n.max[1] - n.min[1]);
	if (n.scale[0] < n.scale[1])
		n.scale[1] = n.scale[0];
	else
		n.scale[0] = n.scale[1];
	n.move[0] = round(n.scale[0] * (CANVAS_W - n.min[0] * 3 + n.max[0]) / 2);
	n.move[1] = round(n.scale[1] * (CANVAS_H - n.min[1] * 3 + n.max[1]) / 2);
	map_iter(map, norm_pixel);
}

void *model2image(void *mlx, t_model *m)
{
	t_image i;
	t_2dmap map;

	(void)mlx;
	i.img = mlx_new_image(mlx, CANVAS_W, CANVAS_H);
	i.addr = mlx_get_data_addr(i.img, &i.bpp, &i.lsize, &i.endian);
	map = model_to_2dmap(m);
	norm_2dmap(map);
	draw_wire(&i, map);
	return i.img;
}

int main(int argc, char **argv)
{
	t_model	*mdl;
	void *mlx;
	void *img;
	void *win;

	PRINT("Start:\n");
	PRINT(" - canvas(width: %d, height: %d)\n", CANVAS_W, CANVAS_H);
	if(argc !=2)
		return 1;
	mlx = mlx_init();
	mlx = NULL;
	mdl = get_model(argv[1]);
	if(mdl == NULL)
		return 1;
	img = model2image(mlx, mdl);
	win = mlx_new_window(mlx, CANVAS_W, CANVAS_H, "fdf");
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_loop(ft_get_global("mlx"));
	(void)win;
	(void)img;
	ft_g_mmfree();
}

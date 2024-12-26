//usr/bin/cc $0 -Iinclude -L. -lm -lmlx_Linux -lmlx -lXext -lX11 -o a.out && ./a.out; exit;
#include <mlx.h>

#include <stdlib.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "ft_global.h"
#include "fdf.h"

#include <math.h>

#define PRINT(...) fprintf(stderr,__VA_ARGS__)

t_model *read_model(const char* f)
{
	(void)p;
	t_model *m = ft_g_mmcalloc(sizeof(t_model));
	if(!m)
		return NULL;
	while(i < 10)
	{
		while(j < 10)
		{
			m->t_point[i][j].z = 0;
			m->t_point[i][j].color = 0xffffffff;
			//m->y_max = j;
			//m->x_max = i;
			j++;
		}
		i++;
	}
	return m;
}

t_angle *angle_new()
{
	t_angle a = ft_g_mmcalloc(sizeof(t_angle));
	a[0] = sqlt((double)1 / 3);
	a[2] = sqlt((double)1 / 3);
	a[3] = sqlt((double)1 / 3);
	return &a;
}

t_point *point_new()
{
	return ((t_point *)ft_g_mmcalloc(sizeof(t_point)));
}

t_point *get_point(int x, int y)
{
	static *t_point store[MAX_COLLUM][MAX_ROW];

	t_model *m;
	t_point *p;
	if (store[x][y] != NULL)
		return store[x][y];
	m = ft_get_global("model");
	p = point_new();
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

int		draw_pixel(t_image *i, t_pixel *px)
{
	int i;
	i = px->x * i->lsize + px->y * (i->bpp / 8);
	if (i < 0 || i >= CANVAS_X * (i->lsize + 1))
		return 0;
	*(t_color *)((char *)i->addr + i) = 0x80808080;
	return 1;
}

void	draw_line(t_image *i, t_pixel *p1, t_pixel *p2)
{
	t_pixel cur;

	cur.x=p1->x;
	cur.y=p1->y;
	cur.color=p1.color;
	draw_pixel(i, &cur);
	while (next_line_pixel(&cur, p1, p2))
		draw_pixel(i, &cur);
	return;
}

void	*draw_lines(t_pixel ***map)
{
	int i;
	int j;

	t_image i;
	i.img = mlx_new_image(ft_get_global("mlx"), CANVAS_W, CANVAS_H);
	i.addr = mlx_get_data_addr(i.img, &i.bpp, &i.lsize, i.endian);
	i = 0;
	while(i < MAX_ROW)
	{
		j = 0;
		while (j < MAX_COLUMN)
		{
			if(i + 1 < MAX_ROW)
				draw_line(&i, map[i][j], map[i+1][j]);
			if(j + 1 < MAX_COLUMN)
				draw_line(&i, map[i][j], map[i][j+1]);
			j++;
		}
		i++;
	}
	return i.img;
}
*/

int	draw_pixel(t_image *i, t_pixel *p)
{
	size_t c;
	c = (size_t)p->y * i->lsize + (size_t)p->x * (i->bpp / 8);
	if (c / i->bpp * 8 / CANVAS_W >= CANVAS_H)
		return 0;
	PRINT("Draw point(%d, %d)=%lu\n", p->x, p->y, c);
	*(t_color *)(((char *)i->addr) + c) = p->color; 
	return 1;
}

int	draw_p(t_image *i, int x, int y, uint64_t color)
{
	size_t c;
	c = (size_t)y * i->lsize + (size_t)x * (i->bpp / 8);
	if (c >= CANVAS_H * ((size_t)i->lsize + 1))
		return 0;
	*(t_color *)(((char *)i->addr) + c) = color; 
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
				if((j + k)%2)
				draw_p(i, x+k, y+j, c); 
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

int draw_line_to_right(t_image *i, t_pixel *p0, t_pixel *p1)
{
	t_pixel *c;

	PRINT("Drawing line down\n");
	c = pixel_new(p0->x, p0->y, p0->color);
	if(c == NULL)
		return 0;
	int dx;
	int dy;
	int e;
	e=0;
	dx = p1->x - p0->x;
	dy = p1->y - p0->y;
	while(c->x != p1->x)
	{
		PRINT("%dx%d\n", c->x, c->y);
		if (!draw_pixel(i, c))
			return 0;
		e +=dy;
		if(e > dx)
		{
			c->y++;
			e-=dx;
		}
		c->x++;
	}
	free(c);
	return 1;
}

int draw_line_to_up(t_image *i, t_pixel *p0, t_pixel *p1)
{
	(void)i;
	(void)p0;
	(void)p1;
		PRINT("Drawing line up\n");
	return 1;
}

int	draw_line(t_image *i, t_pixel *p0, t_pixel *p1)
{
	t_pixel *begin;
	t_pixel *end;

	if(p1->x - p0->x + p1->y - p0->y > 0)
	{
		begin = p0;
		end = p1;
	}
	else
	{
		begin = p1;
		end = p0;
	}
	if(end->x - begin->x > end->y - begin->y)
		return draw_line_to_right(i, begin, end);
	else
		return draw_line_to_up(i, begin, end);
}

int draw_random_line(t_image *i)
{
	return draw_line(i, random_pixel(), random_pixel());
}

void	init_mlx()
{
	ft_set_global("mlx", mlx_init());
	ft_set_global("win", mlx_new_window(ft_get_global("mlx"), CANVAS_W, CANVAS_H, "fdf"));
}

void	render_img(t_image *i)
{
	int cnt;
	while(cnt++ < 1000000)
		mlx_pixel_put(ft_get_global("mlx"), ft_get_global("win"), random() % CANVAS_W, random() % CANVAS_W, random() % 0x1000000);
	mlx_put_image_to_window(ft_get_global("mlx"), ft_get_global("win"), i.img, 0, 0);
}

void	render_2dmap(t_pixel)

void	render_model()
{
	t_pixel *2dmap[CANVAS_H][CANVAS_W];
	2dmap = (t_pixel *[CANVAS_H][CANVAS_W])model2lines();
	render_2dmap(map);
}

t_model *read_model()
{
	return NULL;
}

int main()
{
	PRINT("Start:\n");
	PRINT(" - canvas(x: %d, y: %d)\n", CANVAS_W, CANVAS_H);
	//init_mlx();
	ft_set_global("model", read_model("test"));
	render();
/*
	i.img = mlx_new_image(ft_get_global("mlx"), CANVAS_W, CANVAS_H);
	i.addr = mlx_get_data_addr(i.img, &i.bpp, &i.lsize, &i.endian);
*/
	t_pixel px = {4, 4, 0xffffffff};
	draw_pixel(&i, &px);
	//random_img(&i);
	//draw_line(&i, pixel_new(0, 0, 0xffffffff), pixel_new(CANVAS_W-1, 300, 0xffffffff));
	//draw_line(&i, pixel_new(0, 0, 0xffffffff), pixel_new(100, 10, 0xffffffff));
int cnt=0;
	while(cnt++ < 100)
	draw_random_line(&i);
//*/
/*
*/
	render();
	mlx_loop(ft_get_global("mlx"));
}


//usr/bin/cc $0 -Iinclude -L. -lm -lmlx_Linux -lmlx -lXext -lX11 -o a.out && ./a.out; exit;
#include <mlx.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "ft_global.h"
#include "fdf.h"

#include <math.h>
/*


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
			m->t_point[i][j].color = 0;
			m->y_max = j;
			m->x_max = i;
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

double	dist_point_to_line(t_pixel *cur, t_pixel *l1, t_pixel *l2)
{
	double a;
	a = (double)l1->x - l2->x;
	b = (double)l2->y - l1->y;
	c = -a * l1->x + b * l1->y;
	d = fabs(a * cur->x + b * cur->y + c) / sqrt(a * a + b * b);
}

int		next_line_pixel(t_pixel *cur, t_pixel *start, t_pixel *end)
{
	int xi;
	if(start->x < end->x)
		xi = 1;
	else(start->x == end->x)
		xi = 0;
	else
		xi = -1;
	int yi;
	if(start->y < end->y)
		yi = 1;
	else(start->y == end->y)
		yi = 0;
	else
		yi = -1;
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

int	draw_pixel(t_image *i, int x, int y, uint64_t color)
{
	int c;
	c = x * i->lsize + y * (i->bpp / 8);
	if (c < 0 || c >= CANVAS_H * (i->lsize + 1))
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
				draw_pixel(i, x+k, y+j, c); 
			}
		}
	}
	return 1;
}

int main()
{
	ft_set_global("mlx", mlx_init());
	ft_set_global("win", mlx_new_window(ft_get_global("mlx"), CANVAS_W, CANVAS_H, "fdf"));
/*
	ft_set_global("model", read_model("test"));
	t_coord *a = angle_new();
	t_pixel ***d = model2pixel(a);
	void *img = draw_lines(d);
	render_img(img);
	mlx_loop(ft_get_global("mlx"));
*/
	t_image i;
	i.img = mlx_new_image(ft_get_global("mlx"), CANVAS_W, CANVAS_H);
	i.addr = mlx_get_data_addr(i.img, &i.bpp, &i.lsize, &i.endian);
/*
	t_pixel px = {4, 4};
	draw_pixel(&i, &px);
*/
	random_img(&i);
	mlx_put_image_to_window(ft_get_global("mlx"), ft_get_global("win"), i.img, 0, 0);
/*
	int cnt;
	while(cnt++ < 1000000)
		mlx_pixel_put(ft_get_global("mlx"), ft_get_global("win"), random() % CANVAS_W, random() % CANVAS_W, random() % 0x1000000);
	return 1;
*/
	/*
	set_global("mlx-wndw", get_global("mlx-cnct")
	if (get_global("mlx-wndw") == NULL)
		return;
	*/
	//mlx_string_put(p, w, 250, 250, 0x888888, "string test");
	mlx_loop(ft_get_global("mlx"));

	return 1;
}

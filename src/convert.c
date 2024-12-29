/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:26:07 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/29 16:28:55 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pixel	*point2pixel(t_point *p)
{
	t_pixel	*px;
	int		f[2][3];

	f[0][0] = 90;
	f[0][1] = -110;
	f[0][2] = -1;
	f[1][0] = 70;
	f[1][1] = 107;
	f[1][2] = -13;
	px = pixel_new(p->x * f[0][0] + p->y * f[0][1] + p->z * f[0][2], p->x
			* f[1][0] + p->y * f[1][1] + p->z * f[1][2], p->color);
	return (px);
}

t_pixel	***model2map(t_model *mdl)
{
	t_pixel	***map;
	size_t	x;
	size_t	y;
	size_t	xm;
	size_t	ym;

	xm = max_x(mdl);
	ym = max_y(mdl);
	map = _map_new(xm, ym);
	y = 0;
	while (y < ym)
	{
		while (map[y])
		{
			x = 0;
			while (x < xm)
			{
				set_pixel(map, x, y, point2pixel(get_point(mdl, x, y)));
				x++;
			}
			y++;
		}
	}
	return (map);
}

void	*model2image(void *mlx, t_model *m)
{
	t_image	i;
	t_map	map;

	(void)mlx;
	i.img = mlx_new_image(mlx, CANVAS_W, CANVAS_H);
	i.addr = mlx_get_data_addr(i.img, &i.bpp, &i.lsize, &i.endian);
	map = model2map(m);
	norm_map(map);
	draw_wire(&i, map);
	return (i.img);
}

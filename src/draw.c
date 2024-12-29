/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:29:00 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/29 16:44:36 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	draw_pixel(t_image *i, t_pixel *p)
{
	size_t	c;

	c = (size_t)p->y * i->lsize + (size_t)p->x * (i->bpp / 8);
	if (p->x < 0 || p->y < 0 || p->x >= CANVAS_W || p->y >= CANVAS_H)
		return (0);
	*(t_color *)(((char *)i->addr) + c) = p->color;
	return (1);
}

int	draw_line(t_image *i, t_pixel *p0, t_pixel *p1)
{
	t_pixel	cur;
	t_pixel	delta;
	t_pixel	error;

	if (p0->x > p1->x)
		return (draw_line(i, p1, p0));
	cur = (t_pixel){p0->x, p0->y, p0->color};
	delta = (t_pixel){abs(p1->x - p0->x), abs(p1->y - p0->y), 0x0};
	error = (t_pixel){delta.x - delta.y, 0, 0x0};
	while (cur.x != p1->x || cur.y != p1->y)
	{
		draw_pixel(i, &cur);
		error.y = 2 * error.x;
		if (error.y > -delta.y)
			error.x -= delta.y;
		if (error.y > -delta.y)
			cur.x += (p0->x < p1->x) * 2 - 1;
		if (error.y < delta.x)
			error.x += delta.x;
		if (error.y < delta.x)
			cur.y += (p0->y < p1->y) * 2 - 1;
	}
	draw_pixel(i, &cur);
	return (1);
}

void	draw_wire(t_image *i, t_map map)
{
	size_t	x;
	size_t	y;
	size_t	max_x;
	size_t	max_y;

	y = 0;
	max_x = get_max_x(map);
	max_y = get_max_y(map);
	while (y < max_y)
	{
		x = 0;
		while (x < max_x)
		{
			if (x < max_x - 1)
				draw_line(i, get_pixel(map, x, y), get_pixel(map, x + 1, y));
			if (y < max_y - 1)
				draw_line(i, get_pixel(map, x, y), get_pixel(map, x, y + 1));
			x++;
		}
		y++;
	}
}

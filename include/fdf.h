/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 10:22:23 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/27 01:38:13 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# ifndef CANVAS_W
#  define CANVAS_W 2560
# endif
# ifndef CANVAS_H
#  define CANVAS_H 1600
# endif

# include <stdint.h>
#include <stddef.h>

typedef uint64_t		t_color;
typedef struct s_model	t_model;
typedef struct s_point	t_point;
typedef struct s_image	t_image;
typedef struct s_pixel	t_pixel;

typedef struct s_norm	t_norm;

struct s_norm{
	int		max[2];
	int		min[2];
	double scale[2];
	int		move[2];
};

struct					s_image
{
	void				*img;
	char				*addr;
	int					bpp;
	int					lsize;
	int					endian;
};

struct					s_pixel
{
	int					x;
	int					y;
	uint64_t			color;
};

struct					s_point
{
	int					x;
	int					y;
	int					z;
	t_color				color;
};
// typedef double t_angle[3];

struct					s_model
{
	t_point				p[1000][1000];
	int					min_z;
	int					max_z;
	size_t					x_len;
	size_t					y_len;
};

struct					s_angle
{
};
t_model	*get_model(char *fname);
/*
model					read_model(file);
camera					camera_new(void);
point2line(camera, p1, p2);
map						render(camera, model);
map						render(lines);

void					print_map(map);
*/
#endif

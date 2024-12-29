/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 10:22:23 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/29 16:43:06 by tkondo           ###   ########.fr       */
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

# include "ft_global.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <ft_memory.h>
# include <ft_stdlib.h>
# include <get_next_line.h>
# include <libft.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stddef.h>
# include <stddef.h>
# include <stdint.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef uint64_t		t_color;
typedef struct s_model	t_model;
typedef struct s_point	t_point;
typedef struct s_image	t_image;
typedef struct s_pixel	t_pixel;

typedef t_pixel			***t_map;
typedef struct s_norm	t_norm;

struct					s_norm
{
	int					max[2];
	int					min[2];
	double				scale[2];
	int					move[2];
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

struct					s_model
{
	t_point				p[1000][1000];
	int					min_z;
	int					max_z;
	size_t				x_len;
	size_t				y_len;
};

t_model					*get_model(char *fname);
int						key_hook_esc(int keycode);
int						btn_hook_cross(void);
void					add_hooks(void *win);
t_pixel					*point2pixel(t_point *p);
t_pixel					***model2map(t_model *mdl);
void					*model2image(void *mlx, t_model *m);
int						draw_pixel(t_image *i, t_pixel *p);
int						draw_line(t_image *i, t_pixel *p0, t_pixel *p1);
void					draw_wire(t_image *i, t_map map);
int						key_hook_esc(int keycode);
int						btn_hook_cross(void);
void					add_hooks(void *win);
void					error(const char *s);
int						main(int argc, char **argv);
size_t					get_max_y(t_pixel ***m);
size_t					get_max_x(t_pixel ***m);
void					set_pixel(t_pixel ***m, size_t x, size_t y,
							t_pixel *px);
t_pixel					***_map_new(size_t x, size_t y);
void					map_iter(t_pixel ***map, void (*f)(t_pixel *));
size_t					max_y(t_model *mdl);
size_t					max_x(t_model *mdl);
t_point					*get_point(t_model *m, size_t x, size_t y);
void					search_limit(t_pixel *px);
void					norm_pixel(t_pixel *px);
void					norm_map(t_pixel ***map);
int						ft_isdigits(const unsigned char *s);
char					**mm_split(t_memory_manager *mm, char *s, char c);
char					*mm_gnl(t_memory_manager *mm, int fd);
bool					parse_fdf(t_model *m, int fd, t_memory_manager *mm);
t_model					*get_model(char *fname);
t_pixel					*pixel_new(int x, int y, uint64_t color);
t_pixel					*get_pixel(t_pixel ***m, size_t x, size_t y);
void					scale_pixel(t_pixel *px, double x, double y);
void					move_pixel(t_pixel *px, int x, int y);
#endif

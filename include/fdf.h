#ifndef FDF_H
#define FDF_H

#ifndef CANVAS_W
#define CANVAS_W 1920
#endif
#ifndef CANVAS_H
#define CANVAS_H 1080
#endif

typedef uint64_t t_color;
typedef struct s_model t_model;
typedef struct s_point t_point;
typedef struct s_image t_image;
typedef struct s_pixel t_pixel;

struct s_image
{
	void *img;
	char *addr;
	int	bpp;
	int lsize;
	int endian;
};

struct  s_pixel
{
	int x;
	int y;
	uint64_t color;
};

struct s_point
{
	int x;
	int y;
	int z;
	t_color color;
};
//typedef double t_angle[3];

struct s_model
{
	struct
	{
		int	z;
		unsigned int	color;
	}	s_point [1000][1000];
	int z_min;
	int z_max;
	int y_max;
	int x_max;
};

struct s_angle
{
};

struct map_i
{
	unsigned int top;
	unsigned int left;
	unsigned int color;
};
/*
model read_model(file);
camera camera_new();
point2line(camera, p1, p2);
map render(camera, model);
map render(lines);

void	print_map(map);
*/
#endif

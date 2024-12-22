#ifndef FDF_H
#define FDF_H
typedef struct s_ t_
typedef struct s_model t_model

struct s_window
{
	unsigned int	width;
	unsigned int	height;
}

struct s_model
{
	struct
	{
		unsigned int	z;
		unsigned int	color;
	}	t_point[X_MAX][Y_MAX];
}

struct s_camera
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	z;
	double		roll;
	double		pitch;
	double		yaw;
}

struct map_i
{
	unsigned int top;
	unsigned int left;
	unsigned int color;
}

model read_model(file);
camera camera_new();
point2line(camera, p1, p2);
map render(camera, model);
map render(lines);

void	print_map(map);

#endif

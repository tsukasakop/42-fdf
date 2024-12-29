void draw_oct(t_image *i)
{
	draw_line(i, &((t_pixel){100, 100, 0xffffffff}), &((t_pixel){80, 0, 0xffffffff}));
	draw_line(i, &((t_pixel){100, 100, 0xffffffff}), &((t_pixel){120, 0, 0xffffffff}));
	draw_line(i, &((t_pixel){100, 100, 0xffffffff}), &((t_pixel){80, 200, 0xffffffff}));
	draw_line(i, &((t_pixel){100, 100, 0xffffffff}), &((t_pixel){120, 200, 0xffffffff}));
	draw_line(i, &((t_pixel){100, 100, 0xffffff}), &((t_pixel){0, 80, 0xffffff}));
	draw_line(i, &((t_pixel){100, 100, 0xffffffff}), &((t_pixel){0, 120, 0xffffffff}));
	draw_line(i, &((t_pixel){100, 100, 0xffffff}), &((t_pixel){200, 80, 0xffffff}));
	draw_line(i, &((t_pixel){100, 100, 0xffffffff}), &((t_pixel){200, 120, 0xffffffff}));
}

t_pixel *random_pixel()
{
	t_pixel *px;
	px = pixel_new(random() % CANVAS_H, random() % CANVAS_W, random() % 0x100000000);
	return px;
}

int draw_random_line(t_image *i)
{
	return draw_line(i, random_pixel(), random_pixel());
}

int draw_random_img(t_image *i)
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

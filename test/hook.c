//usr/bin/cc $0 -L./libft -L./libmlx -lm -lmlx -lXext -lX11 -lft -Iinclude -Ilibmlx -Ilibft/include 
#include "../src/hook.c"

int main()
{
	void *mlx;
	void *win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 100, 100, "aiueo");
	mlx_key_hook(win, key_hook_esc, NULL);
	mlx_hook(win, DestroyNotify, NoEventMask, btn_hook_cross, NULL);
	mlx_loop(mlx);
}

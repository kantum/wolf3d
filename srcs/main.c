#include "wolf.h"

void	put_pixel(int x, int y, int color, t_env *e)
{
	if (y < HEIGHT && x < WIDTH &&
			y >= 0 && x >= 0)
		e->data[y * WIDTH + x] = color;
}

void	init_point(t_point *p)
{
	p->x = -1;
	p->y = -1;
	p->color = 0xFFFFFF;
}

int		init(t_env *e)
{
	char	*title;

	title = "Wolf 3D";
	if (!(e->mlx = mlx_init()))
		return (-1);
	e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, title);
	e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	e->data = (int *)mlx_get_data_addr(e->img, &e->bpp, &e->size, &e->endian);
	return (0);
}

void	draw(t_env *e)
{
	int		x;
	int		y;

	x = -1;
	y = -1;
	mlx_clear_window(e->mlx, e->win);
	while (++x < WIDTH)
	{
		while (++y < HEIGHT)
		{
			put_pixel(x, y, 0, e);
		}
		y = -1;
	}
	mlx_put_image_to_window(e->data, e->win, e->img, 0, 0);
}

int		key_hook(int keycode, t_env *e)
{
	if (keycode == KEY_ESCAPE || keycode == KEY_Q)
		quit(e);
	return (0);
}

int		mouse_hook(int button, int x, int y, t_env *e)
{
	(void)e;
	(void)button;
	(void)x;
	(void)y;
	return (0);
}

int		quit(t_env *e)
{
	mlx_destroy_window(e->mlx, e->win);
	exit(0);
}

void	minimap(t_env *e)
{
	int		i;
	int		k;
	int		offx;
	int		offy;
	int		size;

	i = -1;
	k = -1;
	offx = 50;
	offy = 50;
	size = 10;
	while (++i < e->m.height)
	{
		while (++k < e->m.width)
			put_pixel(i * size + offx, k * size + offy,
					e->m.tab[i][k].type == 0 ? 0x00ff00 : 0xff0f0f, e);
		k = -1;
	}
}

int		main(int argc, char **argv)
{
	t_env	e;

	(void)argc;
	(void)argv;
	init(&e);
	if (argc == 2)
		parse(argv[1], &e);
	draw(&e);
	minimap(&e);
	mlx_put_image_to_window(e.data, e.win, e.img, 0, 0);
	mlx_hook(e.win, 17, (1L << 17), quit, &e);
	mlx_key_hook(e.win, key_hook, &e);
	mlx_mouse_hook(e.win, mouse_hook, &e);
	mlx_loop(e.mlx);
}

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

void	init_map(t_env *e)
{
	e->m.offx = 50;
	e->m.offy = 50;
	e->m.size = 20;
}

void	init_hero(t_env *e)
{
	e->h.x = 5.0;
	e->h.y = 11.5;
	e->h.dir.x = 0.0;
	e->h.dir.y = -1.0;
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
	init_hero(e);
	init_map(e);
	e->plane.x = 0.0;
	e->plane.y = 0.66;
	e->time = 0;
	e->oldtime = 0;
	return (0);
}

void	scene(t_env *e)
{
	(void)e;
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
		put_pixel(x,y,0,e);
			scene(e);
		}
		y = -1;
	}
	minimap(e);
	hero(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}

int		quit(t_env *e)
{
	mlx_destroy_window(e->mlx, e->win);
	exit(0);
}

void	hero(t_env *e)
{
	int		size;

	size = -3;
	while(++size < 3)
	{
	put_pixel(e->h.x * e->m.size + e->m.offx + size,
			e->h.y * e->m.size + e->m.offy, 0xff66cc, e);
	put_pixel(e->h.x * e->m.size + e->m.offx,
			e->h.y * e->m.size + e->m.offy + size, 0xff66cc, e);
	}
}

void	minimap(t_env *e)
{
	int		i;
	int		k;

	i = -1;
	k = -1;
	while (++i < e->m.height)
	{
		while (++k < e->m.width)
		{
			if (e->m.tab[i][k] == 1)
				put_pixel(i * e->m.size + e->m.offx, k * e->m.size + e->m.offy, 0x00ff00, e);
			else if (e->m.tab[i][k] == 2)
				put_pixel(i * e->m.size + e->m.offx, k * e->m.size + e->m.offy, 0x0000ff, e);
			else if (e->m.tab[i][k] == 3)
				put_pixel(i * e->m.size + e->m.offx, k * e->m.size + e->m.offy, 0xff0f0f, e);
			else if (e->m.tab[i][k] == 4)
				put_pixel(i * e->m.size + e->m.offx, k * e->m.size + e->m.offy, 0x000fff, e);
		}
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
	hooks(&e);
}

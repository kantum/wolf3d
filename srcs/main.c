#include "wolf.h"

void	put_pixel(int x, int y, int color, t_env *e)
{
	if (y < HEIGHT && x < WIDTH &&
			y >= 0 && x >= 0)
		e->data[y * WIDTH + x] = color;
}

void	draw(t_env *e)
{
	int		x;
	int		y;

	x = -1;
	y = -1;
	while (++x < WIDTH)
	{
		while (++y < HEIGHT)
			put_pixel(x, y, 0xffffff, e);
		y = -1;
	}
	raycast(e);
	if (e->flags & MAP)
		minimap(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}

int		quit(t_env *e)
{
	mlx_destroy_window(e->mlx, e->win);
	exit(0);
}

void	error(t_env *e, int err)
{
	mlx_destroy_window(e->mlx, e->win);
	if (err == NO_ARG)
		ft_putendl_fd("usage: wolf3d [path to map]", 2);
	if (err == TEXTURE_ERR)
		ft_putendl_fd("Error loading texture", 2);
	exit (-1);
}

int		main(int argc, char **argv)
{
	t_env	e;

	(void)argc;
	(void)argv;
	init(&e);
	if (argc == 2)
		parse(argv[1], &e);
	else
		error(&e, NO_ARG);
	draw(&e);
	hooks(&e);
}

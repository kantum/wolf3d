#include "wolf.h"

void	put_pixel(int x, int y, int color, t_env *e)
{
	if (y < HEIGHT && x < WIDTH &&
			y >= 0 && x >= 0)
		e->data[y * WIDTH + x] = color;
}

void	dda1(t_env *e)
{
	if (e->r.dirx < 0)
	{
		e->r.stepx = -1;
		e->r.sidedistx = (e->r.posx - e->r.mapx) * e->r.deltadistx;
	}
	else
	{
		e->r.stepx = 1;
		e->r.sidedistx = (e->r.mapx + 1.0 - e->r.posx) *
			e->r.deltadistx;
	}
	if (e->r.diry < 0)
	{
		e->r.stepy = -1;
		e->r.sidedisty = (e->r.posy - e->r.mapy) * e->r.deltadisty;
	}
	else
	{
		e->r.stepy = 1;
		e->r.sidedisty = (e->r.mapy + 1.0 - e->r.posy) *
			e->r.deltadisty;
	}
}

void	dda2(t_env *e)
{
	while (e->r.hit == 0)
	{
		if (e->r.sidedistx < e->r.sidedisty)
		{
			e->r.sidedistx += e->r.deltadistx;
			e->r.mapx += e->r.stepx;
			e->r.side = 0;
		}
		else
		{
			e->r.sidedisty += e->r.deltadisty;
			e->r.mapy += e->r.stepy;
			e->r.side = 1;
		}
		if (e->m.tab[e->r.mapx][e->r.mapy] > 0)
			e->r.hit = 1;
	}
	if (e->r.side == 0)
		e->r.walldist = (e->r.mapx - e->r.posx + (1 - e->r.stepx) / 2)
			/ e->r.dirx;
	else
		e->r.walldist = (e->r.mapy - e->r.posy + (1 - e->r.stepy) / 2)
			/ e->r.diry;

}

void	vertline(int x, t_env *e)
{
	int	y;
	int	i;
	int	col;

	y = 0;
	i = 0;
	(void)col;
	y = e->r.drawstart;
	while (y < e->r.drawend)
	{
		col = e->r.color[e->m.tab[e->r.mapx][e->r.mapy]];
		if (e->r.side == 0)
			col = col / 2;
		put_pixel(x, y, col, e);
		y++;
	}
}

void	walls(t_env *e)
{
	e->r.lineh = (int)(HEIGHT / e->r.walldist);
	e->r.drawstart = -e->r.lineh / 2 + HEIGHT / 2;
	if (e->r.drawstart < 0)
		e->r.drawstart = 0;
	e->r.drawend = e->r.lineh / 2 + HEIGHT / 2;
	if (e->r.drawend >= HEIGHT)
		e->r.drawend = HEIGHT - 1;
}

void	raycast(t_env *e)
{
	int		x;

	x = -1;
	while (++x < WIDTH)
	{
		e->r.camerax = 2 * x / (float)(WIDTH) - 1;
		e->r.posx = e->h.x;
		e->r.posy = e->h.y;
		e->r.dirx = e->h.dir.x + e->plane.x * e->r.camerax;
		e->r.diry = e->h.dir.y + e->plane.y * e->r.camerax;
		e->r.mapx = (int)(e->r.posx);
		e->r.mapy = (int)(e->r.posy);
		e->r.deltadistx = sqrt(1 + (e->r.diry * e->r.diry) /
			(e->r.dirx * e->r.dirx));
		e->r.deltadisty = sqrt(1 + (e->r.dirx * e->r.dirx) /
			(e->r.diry * e->r.diry));
		e->r.hit = 0;
		dda1(e);
		dda2(e);
		walls(e);
		vertline(x, e);
	}
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
			put_pixel(x , y, 0x000000, e);
		y = -1;
	}
	//e->img = mlx_xpm_file_to_image(e->mlx , "./images/ciel.xpm", &e->size, &e->bpp);
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

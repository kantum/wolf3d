#include "wolf.h"

void	init_point(t_point *p)
{
	p->x = -1;
	p->y = -1;
	p->color = 0xFFFFFF;
}

void	init_map(t_env *e)
{
	e->m.offx = 30;
	e->m.offy = 30;
	e->m.size = 5;
	e->flags ^= MAP;

}

void	init_hero(t_env *e)
{
	e->h.x = 5.0;
	e->h.y = 11.5;
	e->h.dir.x = 0.0;
	e->h.dir.y = -1.0;
}

void	init_raycast(t_env *e)
{
	e->plane.x = 0.66;
	e->plane.y = 0.0;
	e->time = 0;
	e->oldtime = 0;
	e->r.color[0] = WHITE;
	e->r.color[1] = RED;
	e->r.color[2] = GREEN;
	e->r.color[3] = BLUE;
	e->r.color[4] = LBLUE;
	e->r.color[5] = GOLD;
	//e->img = mlx_xpm_file_to_image(e->mlx , "./images/ciel.xpm", &e->tex, &e->bpp);
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
	init_raycast(e);
	return (0);
}



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

int		init(t_env *e, char *arg)
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



int		env_init(t_env *e)
{
}

int		main(int argc, char **argv)
{
	t_env	e;
	
}

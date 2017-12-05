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
	e->h.speed = 0.07;
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
}

void	load_texture(t_env *e)
{
//	int	i;
//	char	str[100] = "./images/tex";
//
//	i = -1;
//	while (++i < NB_TEXTURE -1)
//	{
//		ft_strcat(str, ft_itoa(i));
//		ft_strcat(str, ".xpm");
//		if (!((e->r.voidtex[i] = mlx_xpm_file_to_image(e->mlx,
//							str, &e->texsize, &e->texbpp))))
//			error(e, TEXTURE_ERR);
//		e->r.texture[i] = mlx_get_data_addr(e->r.voidtex[i], &e->bpp, &e->texsize, &e->texendian);
//	}

	if (!((e->r.voidtex[0] = mlx_xpm_file_to_image(e->mlx,
						"./images/tex0.xpm", &e->size, &e->bpp))))
		error(e, TEXTURE_ERR);
	e->r.texture[0] = mlx_get_data_addr(e->r.voidtex[0], &e->bpp, &e->texsize, &e->texendian);
	if (!((e->r.voidtex[1] = mlx_xpm_file_to_image(e->mlx,
						"./images/tex1.xpm", &e->size, &e->bpp))))
		error(e, TEXTURE_ERR);
	e->r.texture[1] = mlx_get_data_addr(e->r.voidtex[1], &e->bpp, &e->texsize, &e->texendian);
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
	load_texture(e);
	init_raycast(e);
	return (0);
}

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
	int	i;
	//char	*str;

	i = -1;
	while (++i < NB_TEXTURE)
		e->r.texture[i] = malloc(sizeof(int*) * TEXWIDTH * TEXHEIGHT);
	i = -1;
//
//	while (++i < NB_TEXTURE -1)
//	{
//		str = malloc(sizeof(char*) * 1024);
//		ft_bzero(str, 1024);
//		ft_strcat(str, "./images/tex");
//		ft_strcat(str, ft_itoa(i));
//		ft_strcat(str, ".ppm");
//		ft_putendl(str);
//		if(!(e->r.texture[i] = ppm_to_array2(str, e)))
//			error(e, TEXTURE_ERR);
//		ft_bzero(str, 1024);
//	}

	//free(str);

	if(!(e->r.texture[0] = ppm_to_array2("./images/tex0.ppm", e)))
		error(e, TEXTURE_ERR);
	if(!(e->r.texture[1] = ppm_to_array2("./images/tex2.ppm", e)))
		error(e, TEXTURE_ERR);
	if(!(e->r.texture[2] = ppm_to_array2("./images/tex0.ppm", e)))
		error(e, TEXTURE_ERR);
	if(!(e->r.texture[3] = ppm_to_array2("./images/tex2.ppm", e)))
		error(e, TEXTURE_ERR);
	//if(!(e->r.texture[4] = ppm_to_array2("./images/tex4.ppm", e)))
	//	error(e, TEXTURE_ERR);
	//if(!(e->r.texture[5] = ppm_to_array2("./images/tex5.ppm", e)))
	//	error(e, TEXTURE_ERR);
	//if(!(e->r.texture[6] = ppm_to_array2("./images/tex6.ppm", e)))
	//	error(e, TEXTURE_ERR);
	//if(!(e->r.texture[7] = ppm_to_array2("./images/tex7.ppm", e)))
	//	error(e, TEXTURE_ERR);
	//if(!(e->r.texture[8] = ppm_to_array2("./images/tex8.ppm", e)))
	//	error(e, TEXTURE_ERR);
//	for(int x = 0; x < TEXWIDTH; x++)
//		for(int y = 0; y < TEXHEIGHT; y++)
//		{
//			int xorcolor = (x * 256 / TEXWIDTH) ^ (y * 256 / TEXHEIGHT);
//			//int xcolor = x * 256 / TEXWIDTH;
//			int ycolor = y * 256 / TEXHEIGHT;
//			int xycolor = y * 128 / TEXHEIGHT + x * 128 / TEXWIDTH;
////			e->r.texture[0][TEXWIDTH * y + x] = 65536 * 254 * (x != y && x != TEXWIDTH - y); //flat red texture with black cross
////			e->r.texture[1][TEXWIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
//			e->r.texture[2][TEXWIDTH * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
//			e->r.texture[3][TEXWIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
//			e->r.texture[4][TEXWIDTH * y + x] = 256 * xorcolor; //xor green
//			e->r.texture[5][TEXWIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
//			e->r.texture[6][TEXWIDTH * y + x] = 65536 * ycolor; //red gradient
//			e->r.texture[7][TEXWIDTH * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
//		}
}

int		init(t_env *e)
{
	char	*title;

	title = "Wolf 3D";
	if (!(e->mlx = mlx_init()))
		return (-1);
	e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, title);
	e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	e->data = (int*)mlx_get_data_addr(e->img, &e->bpp, &e->size, &e->endian);
	init_hero(e);
	init_map(e);
	load_texture(e);
	init_raycast(e);
	return (0);
}

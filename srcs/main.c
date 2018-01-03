/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdurot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 04:34:51 by qdurot            #+#    #+#             */
/*   Updated: 2017/12/10 04:34:51 by qdurot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	put_pixel(int x, int y, int color, t_env *e)
{
	if (y < HEIGHT && x < WIDTH &&
			y >= 0 && x >= 0)
		e->data[y * WIDTH + x] = color;
}

void	draw(t_env *e)
{
	e->oldtime = e->time;
	e->time = clock();
	e->frametime = (e->time - e->oldtime) / 10000.0;
	if (e->img)
		mlx_destroy_image(e->mlx, e->img);
	if (!(e->img = mlx_xpm_file_to_image(e->mlx,
					e->background, &e->width, &e->height)))
		error(e, BG_ERR);
	e->data = (int*)mlx_get_data_addr(e->img, &e->bpp, &e->size, &e->endian);
	raycast(e);
	if (e->flags & MAP)
		minimap(e);
	weapon(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_put_image_to_window(e->mlx, e->win, e->h.imgun, 0, 0);
	e->h.rotspeed = e->frametime * 0.03;
}

int		quit(t_env *e)
{
	int		i;

	i = -1;
	mlx_destroy_window(e->mlx, e->win);
	while (++i < NB_TEXTURE)
		free(e->r.texture[i]);
	i = -1;
	while (++i < e->m.height)
		free(e->m.tab[i]);
	free(e->m.tab);
	exit(0);
}

void	error(t_env *e, int err)
{
	mlx_destroy_window(e->mlx, e->win);
	if (err == NO_ARG)
		ft_putendl_fd("usage: wolf3d [path to map]", 2);
	if (err == TEXTURE_ERR)
		ft_putendl_fd("Error loading texture", 2);
	if (err == OPEN_ERR)
		ft_putendl_fd("Error oppening file", 2);
	if (err == PARSE_ERR)
		ft_putendl_fd("Error parsing map", 2);
	if (err == MALLOC_ERR)
		ft_putendl_fd("Mem alloc error", 2);
	if (err == BG_ERR)
		ft_putendl_fd("Error loading background", 2);
	if (err == GUN_ERR)
		ft_putendl_fd("Error loading weapon", 2);
	if (err == PPM_ERR)
		ft_putendl_fd("Error loading ppm", 2);
	exit(-1);
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

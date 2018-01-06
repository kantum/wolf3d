/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdurot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 04:34:40 by qdurot            #+#    #+#             */
/*   Updated: 2017/12/10 04:34:44 by qdurot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_map(t_env *e)
{
	e->m.offx = 30;
	e->m.offy = 30;
	e->m.size = 5;
	e->flags = MAP;
}

void	init_hero(t_env *e)
{
	e->h.x = 5.0;
	e->h.y = 11.5;
	e->h.dir.x = -0.0;
	e->h.dir.y = -1.0;
	e->h.speed = 0.07;
	e->h.mov = 0;
	e->h.imgun = NULL;
}

void	init_raycast(t_env *e)
{
	e->plane.x = 0.66;
	e->plane.y = 0.0;
	e->time = 0;
	e->oldtime = 0;
}

void	load_texture(t_env *e)
{
	int		i;
	char	*str;
	char	*tmp;

	i = -1;
	while (++i < NB_TEXTURE)
	{
		str = malloc(sizeof(char*) * 1024);
		ft_bzero(str, 1024);
		ft_strcat(str, "./images/env1/tex");
		tmp = ft_itoa(i);
		ft_strcat(str, tmp);
		free(tmp);
		ft_strcat(str, ".ppm");
		if (!(e->r.texture[i] = ppm_to_array(str, e)))
			error(e, TEXTURE_ERR);
		ft_bzero(str, 1024);
		free(str);
	}
}

int		init(t_env *e)
{
	char	*title;

	title = "Wolf 3D";
	if (!(e->mlx = mlx_init()))
		return (-1);
	e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, title);
	e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	e->background = "./images/background/fond1.xpm";
	e->h.gun = "./images/weapons/gun1.xpm";
	e->h.weapon = GUN_1;
	init_hero(e);
	init_map(e);
	load_texture(e);
	init_raycast(e);
	return (0);
}

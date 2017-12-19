/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdurot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:06:35 by qdurot            #+#    #+#             */
/*   Updated: 2017/12/19 16:06:39 by qdurot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	weapon(t_env *e)
{
	int		i;
	int		*data;

	i = -1;
	if (!(e->h.imgun))
	{
		if (!(e->h.imgun = mlx_xpm_file_to_image(e->mlx, e->h.gun,
						&e->width, &e->height)))
			error(e, GUN_ERR);
		data = (int*)mlx_get_data_addr(e->h.imgun,
				&e->bpp, &e->size, &e->endian);
		while (++i < WIDTH * HEIGHT)
			if (data[i] == 0x980088)
				data[i] = 0xFF000000;
	}
}

void	change_weapon(t_env *e)
{
	(void)e;
}

void	shot(t_env *e)
{
	mlx_destroy_image(e->mlx, e->h.imgun);
	e->h.imgun = NULL;
	if (e->h.weapon == GUN_1)
	{
		e->h.gun = "./images/weapons/gun1.xpm";
		e->h.weapon = GUN_2;
	ft_putstr("shot\n");
	}
	else if (e->h.weapon == GUN_2)
	{
		e->h.gun = "./images/weapons/gun2.xpm";
		e->h.weapon = GUN_1;
	}
}

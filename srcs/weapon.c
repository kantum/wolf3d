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
	if (e->h.imgun)
		mlx_destroy_image(e->mlx, e->h.imgun);
	if (e->flags & SHOT)
	{
		if (e->h.weapon == GUN_1)
		{
			e->h.gun = "./images/weapons/gun2.xpm";
			e->h.weapon = GUN_2;
		}
		else if (e->h.weapon == GUN_2)
		{
			e->h.gun = "./images/weapons/gun3.xpm";
			e->h.weapon = GUN_3;
		}
		else if (e->h.weapon == GUN_3)
		{
			e->h.gun = "./images/weapons/gun1.xpm";
			e->h.weapon = GUN_1;
			e->flags ^= SHOT;
		}
	}
	if (!(e->h.imgun = mlx_xpm_file_to_image(e->mlx, e->h.gun,
					&e->width, &e->height)))
		error(e, GUN_ERR);
}

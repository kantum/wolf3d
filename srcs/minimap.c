/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdurot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 04:34:57 by qdurot            #+#    #+#             */
/*   Updated: 2017/12/10 04:34:57 by qdurot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	hero(t_env *e)
{
	int		size;

	size = -3;
	while (++size < 3)
	{
		put_pixel(e->h.y * e->m.size + e->m.offx + size,
				e->h.x * e->m.size + e->m.offy, 0xff66cc, e);
		put_pixel(e->h.y * e->m.size + e->m.offx,
				e->h.x * e->m.size + e->m.offy + size, 0xff66cc, e);
	}
}

int		place_hero(t_env *e)
{
	int	x;
	int	y;

	x = -1;
	while (++x < e->m.height)
	{
		y = -1;
		while (++y < e->m.width)
		{
			if (e->m.tab[x][y] < 0 || e->m.tab[x][y] > 9)
			{
				if ((e->m.tab[x][y] == 'x' - '0') ||
					(e->m.tab[x][y] == 'X' - '0'))
				{
					e->h.x = x + 0.5;
					e->h.y = y + 0.5;
					e->m.tab[x][y] = 0;
				}
				else
					return (0);
			}
		}
	}
	return (1);
}

void	block(int x, int y, int color, t_env *e)
{
	int		i;
	int		k;

	i = -1;
	while (++i < e->m.size)
	{
		k = -1;
		while (++k < e->m.size)
			put_pixel(x * e->m.size + e->m.offx + i,
					y * e->m.size + e->m.offy + k, color, e);
	}
}

void	color_map(int x, int y, t_env *e)
{
	if (e->m.tab[y][x] == 0)
		block(x, y, 0x333e62, e);
	if (e->m.tab[y][x] == 1)
		block(x, y, 0x828E96, e);
	else if (e->m.tab[y][x] == 2)
		block(x, y, 0xffb847, e);
	else if (e->m.tab[y][x] == 3)
		block(x, y, 0x828E96, e);
	else if (e->m.tab[y][x] == 4)
		block(x, y, 0x48dc64, e);
	else if (e->m.tab[y][x] == 5)
		block(x, y, 0x6e707d, e);
	else if (e->m.tab[y][x] == 6)
		block(x, y, 0x633d89, e);
	else if (e->m.tab[y][x] == 7)
		block(x, y, 0x319030, e);
	else if (e->m.tab[y][x] == 8)
		block(x, y, 0xb2199f, e);
	else if (e->m.tab[y][x] == 9)
		block(x, y, 0xfdff84, e);
}

void	minimap(t_env *e)
{
	int		x;
	int		y;

	x = -1;
	while (++x < e->m.width)
	{
		y = -1;
		while (++y < e->m.height)
			color_map(x, y, e);
	}
	hero(e);
}

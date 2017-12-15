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
		put_pixel(e->h.x * e->m.size + e->m.offx + size,
				e->h.y * e->m.size + e->m.offy, 0xff66cc, e);
		put_pixel(e->h.x * e->m.size + e->m.offx,
				e->h.y * e->m.size + e->m.offy + size, 0xff66cc, e);
	}
}

int		place_hero(t_env *e)
{
	int	i;
	int	k;

	i = -1;
	while (++i < e->m.height)
	{
		k = -1;
		while (++k < e->m.width)
		{
			if (e->m.tab[i][k] < 0 || e->m.tab[i][k] > 9)
			{
				if ((e->m.tab[i][k] == 'x' - '0') ||
					(e->m.tab[i][k] == 'X' - '0'))
				{
					e->h.x = i + 0.5;
					e->h.y = k + 0.5;
					e->m.tab[i][k] = 0;
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
	k = -1;
	while (++i < e->m.size)
	{
		while (++k < e->m.size)
			put_pixel(y * e->m.size + e->m.offx + i,
					x * e->m.size + e->m.offy + k, color, e);
		k = -1;
	}
}

void	color_map(int x, int y, t_env *e)
{
	if (e->m.tab[y][x] == 0)
		block(x, y, 0x333e62, e);
	if (e->m.tab[y][x] == 1)
		block(x, y, 0x828E96, e);
	else if (e->m.tab[y][x] == 2)
		block(x, y, 0x249D22, e);
	else if (e->m.tab[y][x] >= 3)
		block(x, y, 0x8D4DB2, e);
	else if (e->m.tab[y][x] == 4)
		block(x, y, 0xff0000, e);
}

void	minimap(t_env *e)
{
	int		y;
	int		x;

	y = -1;
	x = -1;
	e->m.tab2 = (t_point*)malloc(sizeof(t_point) * e->m.height * e->m.width);
	while (++y < e->m.height)
	{
		while (++x < e->m.width)
		{
			e->m.tab2[y * e->m.width + x].x = x * e->m.size + e->m.offx;
			e->m.tab2[y * e->m.width + x].y = y * e->m.size + e->m.offy;
			color_map(x, y, e);
		}
		x = -1;
	}
}

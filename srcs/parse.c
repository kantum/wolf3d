/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdurot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 04:34:59 by qdurot            #+#    #+#             */
/*   Updated: 2017/12/10 04:34:59 by qdurot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	*check_length(t_map *m)
{
	static int	l = 0;

	m->width = ft_strlchr(m->buf, '\n');
	if (!l)
		l = m->width;
	else if (l != m->width)
		return (NULL);
	return (m);
}

static void	*scan_input(t_map *m)
{
	int		ret;
	char	*f_ptr;
	char	rd[BUFF_SIZE + 1];

	m->buf = ft_strnew(0);
	while ((ret = read(m->fd, rd, BUFF_SIZE)))
	{
		if (ret < 0)
			exit(-1);
		rd[ret] = '\0';
		f_ptr = m->buf;
		if (!(m->buf = ft_strjoin(m->buf, rd)) || ret < 0)
			return (NULL);
		free(f_ptr);
	}
	m->width = ft_strlchr(m->buf, '\n');
	m->height = ft_getnline(m->buf);
	free(m->buf);
	close(m->fd);
	return (m);
}

static void	*fill_tab(t_map *m)
{
	int		i;
	int		k;

	i = m->height;
	if (!(m->tab = (int**)malloc(sizeof(int*) * m->height)))
		return (NULL);
	while (get_next_line(m->fd, &m->buf))
	{
		k = -1;
		if (!check_length(m))
			return (NULL);
		m->tab[--i] = (int*)malloc((sizeof(int) * m->width));
		while (++k < m->width)
			m->tab[i][k] = m->buf[k] - '0';
		free(m->buf);
	}
	close(m->fd);
	return (m);
}

int			check_border(t_env *e)
{
	int	i;

	i = -1;
	while (++i < e->m.width)
		if (e->m.tab[0][i] == 0)
			return (0);
	i = -1;
	while (++i < e->m.width)
		if (e->m.tab[e->m.height - 1][i] == 0)
			return (0);
	i = -1;
	while (++i < e->m.height)
		if (e->m.tab[i][0] == 0)
			return (0);
	i = -1;
	while (++i < e->m.height)
		if (e->m.tab[i][e->m.width - 1] == 0)
			return (0);
	return (1);
}

t_env		*parse(char *arg, t_env *e)
{
	if (!(e->m.fd = open(arg, O_RDONLY)))
		error(e, PARSE_ERR);
	if (!scan_input(&e->m))
		error(e, PARSE_ERR);
	if (!(e->m.fd = open(arg, O_RDONLY)))
		error(e, PARSE_ERR);
	if (!fill_tab(&e->m))
		error(e, PARSE_ERR);
	if (e->m.width < 1 || e->m.height < 1)
		error(e, PARSE_ERR);
	if (!place_hero(e))
		error(e, PARSE_ERR);
	if (!check_border(e))
		error(e, PARSE_ERR);
	return (e);
}

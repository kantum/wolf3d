#include "wolf.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int			count_field(char const *s, char c)
{
	int	i;
	int	read;
	int	field;

	i = -1;
	read = 0;
	field = 0;
	while (s[++i] && s[i] != '\n')
	{
		if (s[i] == c)
			read = 0;
		else if (!(s[i] == c) && read == 0)
		{
			read = 1;
			field++;
		}
	}
	return (field);
}

static void	check_length(t_map *m)
{
	static int	l = 0;

	m->width = count_field(m->buf, ' ');
	if (!l)
		l = m->width;
	else if (l != m->width)
		exit(-1);
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
	m->width = count_field(m->buf, ' ');
	m->height = ft_getnline(m->buf);
	free(m->buf);
	close(m->fd);
	return (m);
}

static void	*fill_tab(t_map *m)
{
	char	**tmp;
	int		i;
	int		k;

	i = -1;
	k = -1;
	if (!(m->tab = (t_point**)malloc(sizeof(t_point*) * m->height)))
		return (NULL);
	while (get_next_line(m->fd, &m->buf))
	{
		check_length(m);
		m->tab[++i] = (t_point*)malloc((sizeof(t_point) * m->width));
		tmp = ft_strsplit(m->buf, ' ');
		while (++k < m->width)
		{
			m->tab[i][k].x = k;
			m->tab[i][k].y = i;
			m->tab[i][k].type = ft_atoi(tmp[k]);
		}
		k = -1;
		free(m->buf);
		free_tab(tmp);
	}
	close(m->fd);
	return (m);
}

t_env		*parse(char *arg, t_env *e)
{
	if (!(e->m.fd = open(arg, O_RDONLY)))
		exit(-1);
	if (!scan_input(&e->m))
		exit(-1);
	if (!(e->m.fd = open(arg, O_RDONLY)))
		exit(-1);
	if (!fill_tab(&e->m))
		exit(-1);
	if (e->m.width < 1 || e->m.height < 1)
		exit(-1);
	return (e);
}

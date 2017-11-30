#ifndef WOLF_H
# define WOLF_H
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "mlx.h"
# include "mlx_keys.h"
# include "libft.h"

# define WIDTH 1280
# define HEIGHT 800

# define KEYPRESS			2
# define KEYPRESSMASK		(1L<<0)
# define MOTIONNOTIFY		6
# define POINTERMOTIONMASK	(1L<<6)
# define BUTTONRELEASE		5
# define BUTTONRELEASEMASK	(1L<<3)
# define DESTROYNOTIFY		17
# define STRUCTURENOTIFYMASK	(1L<<17)

typedef struct			s_point
{
	int		x;
	int		y;
	int		type;
	int		color;
}						t_point;

typedef struct			s_map
{
	int		fd;
	int		width;
	int		height;
	char	*buf;
	t_point	*p;
	t_point	**tab;
}						t_map;
typedef struct			s_env
{
	void		*mlx;
	void		*win;
	int			color;
	void		*img;
	int			*data;
	int			size;
	int			bpp;
	int			endian;
	t_point		p;
	t_map		m;
}						t_env;

t_env					*parse(char *arg, t_env *e);
int						quit(t_env *e);

#endif

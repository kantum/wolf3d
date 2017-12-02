#ifndef WOLF_H
# define WOLF_H
# include <unistd.h>
# include <time.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "mlx.h"
# include "mlx_keys.h"
# include "libft.h"

# define WIDTH 1280
# define HEIGHT 800
# define MOVSPEED 0.5
# define ROTSPEED 0.5

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

typedef struct			s_vect
{
	float	x;
	float	y;

}						t_vect;

typedef struct			s_hero
{
	float	x;
	float	y;
	t_vect	dir;
}						t_hero;

typedef struct			s_map
{
	int		fd;
	int		width;
	int		height;
	int		offx;
	int		offy;
	int		zoom;
	int		size;
	char	*buf;
	t_point	*p;
	int		**tab;
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
	t_vect		plane;
	t_hero		h;
	float		movespeed;
	float		rotspeed;
	float		time;
	float		oldtime;
}						t_env;

t_env					*parse(char *arg, t_env *e);
int						quit(t_env *e);
int						mouse_hook(int button, int x, int y, t_env *e);
int						key_hook(int keycode, t_env *e);
int						move(int keycode, t_env *e);
void					scene(t_env *e);
void					minimap(t_env *e);
void					draw(t_env *e);
void					hero(t_env *e);
void					hooks(t_env *e);

#endif

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
# define MOVSPEED 0.15
# define ROTSPEED 0.08

# define MOVUP		1<<0
# define MOVDOWN	1<<1
# define MOVRIGHT	1<<2
# define MOVLEFT	1<<3

# define KEYPRESS			2
# define KEYRELEASE			3
# define KEYPRESSMASK		(1L<<0)
# define KEYRELEASEMASK		(1L<<1)  
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
	short	mov;
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
int						key_press(int keycode, t_env *e);
int						move(t_env *e);
void					scene(t_env *e);
void					minimap(t_env *e);
void					draw(t_env *e);
void					hero(t_env *e);
void					hooks(t_env *e);
int						key_release(int keycode, t_env *e);
int						set_mov(int keycode, t_env *e);
int						loop_hook(t_env *e);
void					movup(t_env *e);
void					movdown(t_env *e);
void					movleft(t_env *e);
void					movright(t_env *e);

#endif

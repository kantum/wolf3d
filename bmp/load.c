/** BITMAP **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct		s_pixel
{
  unsigned char		R;
  unsigned char		G;
  unsigned char		B;
}					t_pixel;

#pragma pack(pop)
#pragma pack(push, 1)
typedef struct		s_bitmap
{
    short			signature;
    int				size;
    short			reserved1;
    short			reserved2;
    int				dataoffSet;
    int				bitmapheadersize;
    int				width;
    int				height;
    short			planes;
    short			bitsperpixel;
    int				compression;
    int				sizeImage;
    int				xpixelspremeter;
    int				ypixelspremeter;
    int				colorsused;
    int				colorsimportant;
}					t_bitmap;
#pragma pack(pop)
/** END BITMAP **/

/**
BITMAP
**/

void *bitmap_to_img(char *filename, t_env *env)
{
	int				i;
	int				j;
	int				k;
	t_bitmap		source_info;
	t_pixel			source_pix;
	unsigned char *datas;

	FILE *fp;
	// ouverture du fichier et verification du sizeof du header
	if(!(fp=fopen(filename,"rb")) || sizeof(source_info) != 54)
		return (NULL);
	// initialisation structure
	memset(&source_info, 0, sizeof(source_info));
	// lecture header
	fread(&source_info, sizeof(source_info), 1, fp);
	// si taille incoherente ou trop grande erreur
	if (source_info.width < 0 || source_info.width > 2000 || source_info.height > 2000 || source_info.height < 0)
		return (NULL);
	// position du fd sur l'offset des datas
	fseek(fp, source_info.dataoffSet, SEEK_SET);
	// malloc datas, nb pixel * 3 (R, G, B)
	datas = (unsigned char *)malloc(sizeof(unsigned char) * source_info.width * source_info.height * 3);
	i = 0;
	j = 0;
	k = 0;
	// recuperation des donnes, si width % 4 != 0 alors padding
	while (i < source_info.height)
	{
		k = 0;
		while (k < source_info.width)
		{
			fread(&source_pix, sizeof(t_pixel), 1, fp);
			datas[j++] = source_pix.R;
			datas[j++] = source_pix.G;
			datas[j++] = source_pix.B;
			k++;
		}
		// padding
		if (k % 4 != 0)
			fread(NULL, k % 4, 1, fp);
		i++;
	}
	// creation image et copies des donnes, ATTENTION, la premiere ligne d'un bmp est la derniere, leture ligne par ligne en partant de la fin
	void *img = mlx_new_image(env->mlx, source_info.width, source_info.height);
	if (img)
	{
		char	*idatas;
		int		bpx;
		int		linesize;
		int		indian;
		idatas =  mlx_get_data_addr(img, &bpx, &linesize, &indian);
		i = 0;
		k = 0;
		while ((int)i < source_info.height)
		{
			j = 0;
			k = (source_info.height - 1 - i) * (source_info.width * 3);
			while ((int)j < source_info.width)
			{
				int index = i * linesize + ((j * bpx) >> 3);
				
				idatas[index] = datas[k++];
				idatas[++index] = datas[k++];
				idatas[++index] = datas[k++];
				j++;
			}
			i++;
		}
		// test debug display
		mlx_put_image_to_window(env->mlx, env->win, img, 0, 0);
	}
	free(datas);
	fclose(fp);
	return (img);
}
/** END BITMAP **/

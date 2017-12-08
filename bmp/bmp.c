#include "bmp.h"

typedef struct		s_bmp
{
	int		header_size;
	int		offset;
	int		width;
	int		height;
	int		col_planes;
	int		bpp;
	int		compres;
	int		img_size;
	int		h_res;
	int		v_res;
	int		palet;
	int		imp_color;
}					t_bmp;

int		*bmp(char *path)
{
	FILE *fp = fopen(path,"rb");
 
    // détermine la taille du fichier BMP
    fseek(fp, 0, SEEK_END);
    size_t fileSize = ftell(fp);
 
    printf("%lu\n\n", fileSize);
 
    fseek(fp, 0, SEEK_SET);
 
    // allocation d'un tableau de la taille du fichier
    unsigned char *bmparray = malloc(fileSize * sizeof(unsigned char));
	t_bmp	image;
 
    // chargement du fichier bmp en mémoire
    int count = 0;
    int c;
 
    while((c = fgetc(fp)) != EOF)
        bmparray[count++] = c;
 
    // affichage du tableau
	int	i;
	i = -1;
	while (++i < fileSize)
	{
		if (i % 16)
			printf("%.2x ", bmparray[i]);
		else
		printf("\n");
	}
 
	printf("\n");
	printf("\n");

	printf("bitmap magic : %c%c\n", bmparray[0x0],bmparray[0x1]);

	printf("bmp header size : %d\n", bmparray[0x0E]);

	printf("offset : %d\n", bmparray[0xA]);
	
	printf("img width : %d\n", bmparray[0x12]);

	printf("img height : %d\n", bmparray[0x16]);

	printf("color plane (must be 1) : %d\n", bmparray[0x1A]);

	printf("img bit per pixel : %d\n", bmparray[0x1C]);

	printf("compression method : %d\n", bmparray[0x1E]);

	printf("image size : %d\n", bmparray[0x22]); //what is BI_RGB ?

	printf("horizontall resolution : %d\n", bmparray[0x26]);

	printf("vertical resolution : %d\n", bmparray[0x2A]);

	printf("number of color in the palette : %d\n", bmparray[0x2E]);

	printf("number of important colors : %d\n", bmparray[0x32]);

	void	*tab;

	tab = malloc(sizeof(int *) * bmparray[0x12] * bmparray[0x16]); 


	unsigned int test = *((unsigned int*)&bmparray[bmparray[0xA]]);
	
    printf("#%u\n\n", test);

    unsigned int byte = *((unsigned int*)&bmparray[55]);
 
    printf("#%u\n\n", byte);
 
    // affichage de la variable byte octet par octet

	i = -1;
		while (++i < bmparray[0x1C])
        printf("%.x", *((unsigned char*)(&byte) + i));
 
    printf("\n\n");
 
    free(bmparray);
    fclose(fp);
    return 0;
}

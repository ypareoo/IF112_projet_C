#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct color{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

struct picture{
    int width;
    int height;
    struct color* pixels;

};


struct picture new_pic(int width, int height){
    struct picture retour;
    retour.width = width;
    retour.height = height;
    retour.pixels = (struct color*) malloc(sizeof(struct color)*width*height);
    return retour;
}

void save_picture(struct picture pic,char* nom_fichier){
    //char* filename = "mandelbrot_via_struct.ppm";
    FILE * fp = fopen(nom_fichier,"w");
    fprintf(fp, "P6 %d %d 255 ",pic.width,pic.height); //bits qui stockent les caractéristiques du fichier

    for(int i=0;i<pic.height;i++){
        for(int j=0;j<pic.width;j++){
            fwrite(&(pic.pixels[j+i*pic.width].red),sizeof(char),1,fp);
            fwrite(&(pic.pixels[j+i*pic.width].green),sizeof(char),1,fp);
            fwrite(&(pic.pixels[j+i*pic.width].blue),sizeof(char),1,fp);


            //printf("t: ça converge ? %d\n",convergence(coordonnee_x,coordonnee_y));
        }
    }
    fclose(fp);
}
void set_pixel(struct picture pic,int x,int y,unsigned char rouge,unsigned char vert,unsigned char bleu){
    pic.pixels[y+x*pic.width].red = rouge;
    pic.pixels[y+x*pic.width].green = vert;
    pic.pixels[y+x*pic.width].blue = bleu;
}

int main(){
    struct picture ma_photo = new_pic(2,2);
    set_pixel(ma_photo,0,0,0,0,0);
    set_pixel(ma_photo,0,1,0,255,0);
    set_pixel(ma_photo,1,0,255,0,0);
    set_pixel(ma_photo,1,1,0,0,255);
    save_picture(ma_photo,"mon_image.ppm");
    printf("t:FIN\n");
}
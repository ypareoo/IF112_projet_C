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
    for (int i=0;i<width*height;i++){
        retour.pixels[i].red = 0;
        retour.pixels[i].green = 0;
        retour.pixels[i].blue = 0;
    }
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
    pic.pixels[x+y*pic.width].red = rouge;
    pic.pixels[x+y*pic.width].green = vert;
    pic.pixels[x+y*pic.width].blue = bleu;
}

void trace_ligne(struct picture pic,int x1,int y1,int x2,int y2,unsigned char rouge,unsigned char vert,unsigned char bleu){
    int max;
    if (abs(x1-x2) > abs(y1-y2)){
        max = abs(x1-x2);
    }
    else{
        max = abs(y1-y2);
    }
    int n = max + 1;
    int x = x1;
    int y = y1;
    printf("t:n=%d\n",n);
    for (int i = 0; i<n; i++){
        pic.pixels[x+y*pic.width].red = rouge;
        pic.pixels[x+y*pic.width].green = vert;
        pic.pixels[x+y*pic.width].blue = bleu;
        if (x1 - x2){
            if (x2 > x1){
                x += 1;
            }
            else{
                x-=1;
            }
        }
        if (y1 - y2){
            if (y2 > y1){
                y += 1;
            }
            else{
                y -= 1;
            }
        }
        printf("t:i=%d\n",i);
    }
}

int main(){
    struct picture ma_photo = new_pic(10,10);
    trace_ligne(ma_photo,2,2,7,7,255,0,0);
    trace_ligne(ma_photo,2,7,7,2,0,0,255);
    trace_ligne(ma_photo,1,2,1,7,0,255,0);
    trace_ligne(ma_photo,8,2,8,7,0,255,0);
    trace_ligne(ma_photo,2,1,7,1,255,0,255);
    trace_ligne(ma_photo,2,8,7,8,255,0,255);
    //set_pixel(ma_photo,5,5,255,255,255);
    save_picture(ma_photo,"mon_image.ppm");
    free(ma_photo.pixels);
    printf("t:FIN\n");
}
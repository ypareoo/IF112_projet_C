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
                x = x1 + roundf((float) ((float) (x2-x1+1)/n)*(i+1));
                printf("t: x = %d\n",x);
            }
            else{
                x = x1 - roundf((float) ((float) (x1-x2+1)/n)*(i+1));
            }
        }
        if (y1 - y2){
            if (y2 > y1){
                y = y1 + roundf((float) ((float) (y2-y1+1)/n)*(i+1));
            }
            else{
                y = y1 - roundf((float) ((float) (y1-y2+1)/n)*(i+1));
            }
        }
        printf("t:i=%d\n",i);
    }
}

void read_picture(struct picture pic,char* nom_fichier){
    //char* filename = "mandelbrot_via_struct.ppm";
    FILE * fp = fopen(nom_fichier,"r");
    float x1,y1,x2,y2;
    while(fscanf(fp, "%f %f %f %f ",&x1,&y1,&x2,&y2) == 4){
        printf("t: %f %f %f %f \n",x1,y1,x2,y2);
        int xint1= roundf(x1);
        int yint1 = roundf(y1);
        int xint2 = roundf(x2);
        int yint2 = roundf(y2);
        printf("t: %d %d %d %d \n",xint1,yint1,xint2,yint2);
        trace_ligne(pic,x1,y1,x2,y2,255,255,255);
    }

    fclose(fp);
}

int main(){
    struct picture ma_photo = new_pic(500,500);
    read_picture(ma_photo,"kang.txt");
    save_picture(ma_photo,"image_vectorielle_kang.ppm");
    free(ma_photo.pixels);
    printf("t:FIN\n");
}
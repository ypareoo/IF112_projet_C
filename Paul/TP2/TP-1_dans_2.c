#include <stdio.h>
#include <math.h>

#define HAUTEUR 600
#define LARGEUR 900

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} color;

typedef struct {
    int width;
    int height;
    double Xmin;
    double Ymin;
    double Xmax;
    double Ymax;
    double scale;
    double pixwidth;
    int * convrg;
} mandel_pic;

color palette(int c){
    color retour;
    int c_modulo = c;
    if (c >= 1792){
        c_modulo = ((c - 256) % 1536) + 256;
    }
    else {
        c_modulo = c;
    }
        
    if  (c_modulo >= 0&& c_modulo <= 255){
        retour.red = c_modulo;
        retour.green = 0;
        retour.blue = 0;
    }
    if (c_modulo >= 256 && c_modulo <= 511){
        retour.red = 255;
        retour.green = c_modulo - 256; // montee
        retour.blue = 0;
    }
    if (c_modulo >= 512 && c_modulo <= 767){
        retour.red = 767 - c_modulo; //descente
        retour.green = 255;
        retour.blue = 0;
    }
    if (c_modulo >= 768 && c_modulo <= 1023){
        retour.red = 0;
        retour.green = 255;
        retour.blue = c_modulo - 768;
    }
    if (c_modulo >= 1024 && c_modulo <= 1279){
        retour.red = 0;
        retour.green = 1279 - c_modulo;
        retour.blue = 255;
    }
    if (c_modulo >= 1280 && c_modulo <= 1535){
        retour.red = c_modulo - 1280;
        retour.green = 0;
        retour.blue = 255;
    }
    if (c_modulo >= 1536 && c_modulo <= 1791){
        retour.red = 255;
        retour.green = 0;
        retour.blue = 1792 - c_modulo;
    }
    if (c_modulo > 1791){
        printf("t: c_modulo = %d\n",c_modulo);
    }
    return retour;
}

// préciser l'ensemble des pixels
void create_disque(int w, int h, int rayon){
    char* filename = "dique.ppm";
    FILE * fp = fopen(filename,"w");
    fprintf(fp, "P6 %d %d 255 ",w,h); //bits qui stockent les caractéristiques du fichier
    char r=255;
    char g=255;
    char b=255;

    char r_bis=0;
    char g_bis=0;
    char b_bis=0;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            float distance_centre = sqrt(pow(((h/2)-i),2)+pow((j-(w/2)),2));    //pow -> mise au carré ici
            if (distance_centre <= 150){
                fwrite(&r_bis,sizeof(char),1,fp);
                fwrite(&g_bis,sizeof(char),1,fp);
                fwrite(&b_bis,sizeof(char),1,fp);
            }
            else {
                fwrite(&r,sizeof(char),1,fp);
                fwrite(&g,sizeof(char),1,fp);
                fwrite(&b,sizeof(char),1,fp);
            }
        }
    }
    fclose(fp);
}

int convergence(float x, float y){
    float u_x = x;
    float u_y = y;
    float u_x_avant = u_x;
    for (int i = 0; i<85;i++){
        //u=u²+Z
        u_x_avant = u_x;
        u_x = u_x*u_x - u_y*u_y + x;
        u_y = 2*u_x_avant*u_y + y;
        if (sqrt(u_x*u_x + u_y*u_y) >= 2){
            return i+1;
        }
    }
    return 0;
    
}

void create_image_mandelbrot(int w, int h){
    char* filename = "mandelbrot_bis.ppm";
    FILE * fp = fopen(filename,"w");
    fprintf(fp, "P6 %d %d 255 ",w,h); //bits qui stockent les caractéristiques du fichier
    char r=255;
    char g=255;
    char b=255;

    char r_bis=0;
    //char g_bis=0;
    char b_bis=0;
    float coordonnee_x;
    float coordonnee_y;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            coordonnee_x = (3.0/899.0)* (float) j- (float) 2;
            coordonnee_y = (-2.0/599.0)* (float) i + (float) 1;

            color couleur = palette(convergence(coordonnee_x,coordonnee_y)*15); // multiple de trois
            /*r_bis=0;
            char g_bis=3*convergence(coordonnee_x,coordonnee_y);
            b_bis=255;*/
            /*r_bis=0;
            char g_bis=couleur.green;
            b_bis=255;*/
            /*fwrite(&r_bis,sizeof(char),1,fp);
            fwrite(&g_bis,sizeof(char),1,fp);
            fwrite(&b_bis,sizeof(char),1,fp);*/

            fwrite(&(couleur.red),sizeof(char),1,fp);
            fwrite(&(couleur.green),sizeof(char),1,fp);
            fwrite(&(couleur.blue),sizeof(char),1,fp);

            //printf("t: ça converge ? %d\n",convergence(coordonnee_x,coordonnee_y));
        }
    }
    fclose(fp);
}



int main(){
    //create_img(10,10);
    //create_disque(600,400,100);
    //printf("t: ça converge ? %d\n",convergence(-1,0.29));
    create_image_mandelbrot(LARGEUR,HAUTEUR);
}


void create_img(int w, int h){
    char* filename = "test.ppm";
    FILE * fp = fopen(filename,"w");
    fprintf(fp, "P6 %d %d 255 ",w,h); //bits qui stockent les caractéristiques du fichier
    char r=255;
    char g=0;        
    char b=0;
    for(int i=0;i<h*w;i++){
        fwrite(&r,sizeof(char),1,fp);
        fwrite(&g,sizeof(char),1,fp);
        fwrite(&b,sizeof(char),1,fp);
    }
    fclose(fp);
}
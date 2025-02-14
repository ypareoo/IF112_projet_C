#include <stdio.h>
#include <math.h>

#define HAUTEUR 600
#define LARGEUR 900
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
            r_bis=0;
            char g_bis=3*convergence(coordonnee_x,coordonnee_y);
            b_bis=255;
            fwrite(&r_bis,sizeof(char),1,fp);
            fwrite(&g_bis,sizeof(char),1,fp);
            fwrite(&b_bis,sizeof(char),1,fp);
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
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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


int interpolate(mandel_pic old_pic, double x, double y) {
    //To force computation of new pixels
    //if (random() < RAND_MAX*REFRESH_PROB)
        //return -1;
    
    //Outside the previous image
    //or equal, to avoid border effects in the 4 neighbors interpolation
    if (x < old_pic.Xmin) 
        return -1;
    if (x > old_pic.Xmax) 
        return -1;
    if (y < old_pic.Ymin) 
        return -1;
    if (y > old_pic.Ymax)
        return -1;
    
    double val;
    double xindex, yindex;
    int xi, yi;

    //Projection of new coordinates in the old 
    xindex = (x - old_pic.Xmin)/old_pic.pixwidth; //Between 0-width
    yindex = (y - old_pic.Ymin)/old_pic.pixwidth; //Between 0-height
    xi = xindex;
    yi = yindex;

    //For closest point,
    return old_pic.convrg[xi + old_pic.width*(yi)];

    //Interpolation with 4 neighbors
    //To complete
}


mandel_pic new_mandel(int width, int height, double Xmin, double Ymin, double scale){
    mandel_pic retour;
    retour.Xmax = Xmin + (scale*3.0);
    retour.Ymax = Ymin + (scale*3.0*((float) height/(float)width)); // (float) nécessaire sinon la fraction renvoie zéro
    retour.pixwidth = scale*(3.0/width);

    retour.width = width;
    retour.height = height;
    retour.Xmin = Xmin;
    retour.Ymin = Ymin;
    retour.scale = scale;
    retour.convrg = (int*) malloc(sizeof(int)*width*height);
    return retour;
}

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

    float coordonnee_x;
    float coordonnee_y;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            coordonnee_x = (3.0/(w-1))* (float) j- (float) 2;
            coordonnee_y = (-2.0/(h-1))* (float) i + (float) 1;

            color couleur = palette(convergence(coordonnee_x,coordonnee_y)*15); // multiple de trois

            fwrite(&(couleur.red),sizeof(char),1,fp);
            fwrite(&(couleur.green),sizeof(char),1,fp);
            fwrite(&(couleur.blue),sizeof(char),1,fp);

            //printf("t: ça converge ? %d\n",convergence(coordonnee_x,coordonnee_y));
        }
    }
    fclose(fp);
}

void save_mandel(mandel_pic mandel,char* nom_fichier){
    //char* filename = "mandelbrot_via_struct.ppm";
    FILE * fp = fopen(nom_fichier,"w");
    fprintf(fp, "P6 %d %d 255 ",mandel.width,mandel.height); //bits qui stockent les caractéristiques du fichier

    for(int i=0;i<mandel.height;i++){
        for(int j=0;j<mandel.width;j++){

            color couleur = palette(mandel.convrg[j+i*mandel.width]*15); // multiple de trois

            fwrite(&(couleur.red),sizeof(char),1,fp);
            fwrite(&(couleur.green),sizeof(char),1,fp);
            fwrite(&(couleur.blue),sizeof(char),1,fp);

            //printf("t: ça converge ? %d\n",convergence(coordonnee_x,coordonnee_y));
        }
    }
    fclose(fp);
}

mandel_pic create_struct_mandelbrot(int w, int h, double x_min, double y_min, double scale){
    mandel_pic ma_structure_mandel = new_mandel(w,h,x_min,y_min,scale);
    float coordonnee_x;
    float coordonnee_y;
    printf("t: %f\n",y_min);
    printf("t: %f\n",ma_structure_mandel.Ymax);
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            coordonnee_x = ((float) (ma_structure_mandel.Xmax - x_min)/(w-1))* (float) j + (float) x_min; //résonner sur le signe de x_min
            coordonnee_y = ((float) (y_min - ma_structure_mandel.Ymax)/(h-1))* (float) i - (float) y_min;

            ma_structure_mandel.convrg[j+i*w] = convergence(coordonnee_x,coordonnee_y);
        }
    }
    return ma_structure_mandel;
}
mandel_pic interpolation_mandelbrot(mandel_pic old_structure,int w, int h, double x_min, double y_min, double scale){
    mandel_pic ma_structure_mandel = new_mandel(w,h,x_min,y_min,scale);
    float coordonnee_x;
    float coordonnee_y;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            coordonnee_x = ((ma_structure_mandel.Xmax - x_min)/(w-1))* (float) j + (float) x_min; //résonner sur le signe de x_min
            coordonnee_y = ((y_min - ma_structure_mandel.Ymax)/(h-1))* (float) i - (float) y_min;
            

            ma_structure_mandel.convrg[j+i*w] = interpolate(old_structure,coordonnee_x,coordonnee_y);
        }
    }
    return ma_structure_mandel;
}



int main(){
    //create_img(10,10);
    //printf("t: ça converge ? %d\n",convergence(-1,0.29));
    create_image_mandelbrot(LARGEUR,HAUTEUR);
    mandel_pic structure_mandel = create_struct_mandelbrot(LARGEUR,HAUTEUR,-0.755232,0.121387,0.01);
    //mandel_pic structure_mandel = interpolation_mandelbrot(LARGEUR,HAUTEUR,-0.752914,0.123475,0.00738);
    //printf("%d \n",interpolate(structure_mandel,-0.755232,0.121387));
    save_mandel(structure_mandel,"mandelbrot_via_struct.ppm");
    free(structure_mandel.convrg);
    printf("t:FIN\n");
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
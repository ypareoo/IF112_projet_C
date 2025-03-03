#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define x1 -2.0
#define y1 1.0
#define x2 1.0
#define y2 -1.0

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
}color;

struct mandel_pic {
    int width;
    int height;
    double Xmin;
    double Ymin;
    double Xmax;
    double Ymax;
    double scale;
    double pixwidth;
    int* convrg;
};

color palette (int c){
    int cbis=c%1793;
    color col;
    if (cbis>=0 && cbis<=255){
        col.red=cbis;
        col.green=0;
        col.blue=0;
    }
    else if (cbis>=256 && cbis<=511){
        col.red=255;
        col.green=cbis-256;
        col.blue=0;
    }
    else if (cbis>=512 && cbis<=767){
        col.red=767-cbis;
        col.green=255;
        col.blue=0;
    }
    else if (cbis>=768 && cbis<=1023){
        col.red=0;
        col.green=255;
        col.blue=cbis-768;
    }
    else if (cbis>=1024 && cbis <=1279){
        col.red=0;
        col.green=1023-cbis;
        col.blue=255;
    }
    else if (cbis>=1280 && cbis<=1535){
        col.red=cbis-1280;
        col.green=0;
        col.blue=255;
    }
    else{
        col.red=255;
        col.green=0;
        col.blue=cbis-1536;
    }
    return col;
}




int convergence (double x,double y){
    float z_real = x;
    float z_im = y;
    int iter=0;
    while((z_real*z_real)+(z_im*z_im)<=4 && iter<85){
        float tmp = z_real*z_real+x-z_im*z_im;
        z_im=y+2.0*z_im*z_real;
        z_real=tmp;
        iter++;
    }
    //if ((z_real*z_real)+(z_im*z_im)<=4 && iter==85){
     //   iter=0;
    //}
    //printf("%d\n",iter);
    return iter*10;
}



struct mandel_pic new_mandel(int width, int height, double Xmin, double Ymin, double scale){
    struct mandel_pic m;
    m.scale=scale;
    m.width=width;
    m.height=height;
    m.Xmin=Xmin;
    m.Ymin=Ymin;
    m.Xmax=Xmin+(m.scale*3.0);
    m.Ymax=Ymin+(scale*3*height/width);
    m.pixwidth=scale*3.0/width;
    m.convrg=(int*)calloc((m.Xmax-m.Xmin)*(m.Ymax-m.Ymin), sizeof(int));
    //printf("Xmin %lf, Ymin %lf, Xmax %lf, Ymax %lf\n",m.Xmin,m.Ymin,m.Xmax,m.Ymax);
}



void save_mandel(struct mandel_pic,char* filename){
    struct mandel_pic m;
    int width = m.width;
    int height = m.height;
    //filename="mandelbrot5.ppm";
    FILE* fp=fopen(filename,"w");
    fprintf(fp,"P6 %d %d 255 ",width,height);


    char r=0;
    char g=0;
    char b=0;
    int c=2;
    for (int i=0;i<height;i++){
        for (int j=0;j<width;j++){
            color col=palette(c);
            r=col.red;
            g=col.green;
            b=col.blue;
            fwrite(&r,sizeof(char),1,fp);
            fwrite(&g,sizeof(char),1,fp);
            fwrite(&b,sizeof(char),1,fp);
        }
    }

}


void mandelbrot2 (int w, int h){
    new_mandel(w,h,x1,y1,1.0);
    double real;
    double imag;
    for (int i=0;i<h;i++){
        for (int j=0;j<w;j++){
            real = x1 + ((double)j/(double)(w-1))*(x2-x1);
            imag = y1 + ((double)i/(double)(h-1))*(y2-y1);
            //real = (3.0/899.0)* (double) j- (double) 2;
            //imag = (-2.0/599.0)* (double) i + (double) 1;

            //int iter = convergence(real,imag);

            new_mandel(w,h,real,imag,1.0);
        }
    }
}




void mandelbrot (int w, int h){
    char* filename="mandelbrot4.ppm";
    FILE* fp=fopen(filename,"w");
    fprintf(fp,"P6 %d %d 255 ",w,h);

    char r=0;
    char g=0;
    char b=0;
    double real;
    double imag;
    for (int i=0;i<h;i++){
        for (int j=0;j<w;j++){
            real = x1 + ((double)j/(double)(w-1))*(x2-x1);
            imag = y1 + ((double)i/(double)(h-1))*(y2-y1);
            //real = (3.0/899.0)* (double) j- (double) 2;
            //imag = (-2.0/599.0)* (double) i + (double) 1;

            int iter = convergence(real,imag);

            //r=(iter%256);
            //g=(3*iter)%256;
            //b=(iter*15)%256;
            color col=palette(iter);
            r=col.red;
            g=col.green;
            b=col.blue;
            fwrite(&r,sizeof(char),1,fp);
            fwrite(&g,sizeof(char),1,fp);
            fwrite(&b,sizeof(char),1,fp);
        }
    }
    fclose(fp);
}



int main(){

    /*convergence (-1.0,2.0);
    convergence(-1.0,1.5);
    convergence(-1.0,1.0);
    convergence(-1.0,0.5);
    convergence(-1.0,0.4);
    convergence(-1.0,0.35);
    convergence(-1.0,0.3);
    convergence(-1.0,0.29);
    convergence(-1.0,0.28);*/

    struct mandel_pic m;
    //m.width=900;
    //m.height=600;
    new_mandel(900, 600, x1, y1, 1.0);

    mandelbrot(900,600);
    mandelbrot2(900,600);
    save_mandel(m,"mandelbrot5.ppm");

    return 0;
}
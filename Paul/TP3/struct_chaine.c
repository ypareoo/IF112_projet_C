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

struct vector{
    double x1;
    double y1;
    double x2;
    double y2;
    struct vector * next;
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
        //printf("t: %f %f %f %f \n",x1,y1,x2,y2);
        /*int xint1= roundf(x1);
        int yint1 = roundf(y1);
        int xint2 = roundf(x2);
        int yint2 = roundf(y2);*/
        //printf("t: %d %d %d %d \n",xint1,yint1,xint2,yint2);
        trace_ligne(pic,x1,y1,x2,y2,255,255,255);
    }

    fclose(fp);
}

struct vector* read_vector_file(char* nom_fichier){
    struct vector * premier_elm = NULL;
    struct vector * elm_en_cours = premier_elm;
    FILE * fp = fopen(nom_fichier,"r");
    float x1,y1,x2,y2;
    while(fscanf(fp, "%f %f %f %f ",&x1,&y1,&x2,&y2) == 4){

        struct vector* new_elm = (struct vector *) malloc(sizeof(struct vector));
        new_elm->x1 = x1;
        new_elm->y1 = y1;
        new_elm->x2 = x2;
        new_elm->y2 = y2;
        new_elm->next = elm_en_cours;
        elm_en_cours = new_elm;
        printf("t: on est là \n");
    }

    fclose(fp);
    return elm_en_cours;
}

void draw_vector(struct picture pic,struct vector* vecteur,struct color couleur){

    //malloc à désallouer ??
    while (vecteur->next != NULL){
        trace_ligne(pic,vecteur->x1,vecteur->y1,vecteur->x2,vecteur->y2,couleur.red,couleur.green,couleur.blue);
        vecteur = vecteur->next;
        printf("t: on est ici \n");
    }
}

void scale_vector(struct vector* vecteur,double scale){

    //malloc à désallouer ??
    while (vecteur->next != NULL){
        vecteur->x1 *= scale;
        vecteur->y1 *= scale;
        vecteur->x2 *= scale;
        vecteur->y2 *= scale;
        vecteur = vecteur->next;
        printf("t: on est ici \n");
    }
}

int main(){
    struct color jaune;
    jaune.red = 255;
    jaune.green = 255;
    jaune.blue = 0;
    struct picture ma_photo = new_pic(500,500);
    //read_picture(ma_photo,"kang.txt");
    struct vector* liste = read_vector_file("cat.txt");
    scale_vector(liste,0.5);
    draw_vector(ma_photo,liste,jaune);
    save_picture(ma_photo,"image_vectorielle_chaine_cat.ppm");
    free(ma_photo.pixels);
    printf("t:FIN\n");
}
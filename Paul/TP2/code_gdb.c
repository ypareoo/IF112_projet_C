#include<stdio.h>
#include<stdlib.h>

typedef struct {
  int lines;
  int cols;
  double* ptr;
} matrix;

matrix new_matrix(int lines, int cols) {
  matrix mat;
  mat.lines = lines;
  mat.cols = cols;
  mat.ptr = (double*) calloc(lines*cols, sizeof(double));
  return mat;
}

matrix fill_matrix(matrix mat) {
  for (int i=0; i<mat.lines*mat.cols; i++)
    mat.ptr[i] = rand()%10;
  return mat;
}

double get_matrix_value(matrix mat, int line, int col) {
  return mat.ptr[col+line*mat.cols];
}

void disp_matrix(matrix mat) {
  for (int i=0; i<mat.lines; i++)  {
    for (int j=0; j<mat.cols; j++)
      printf("%d ", (int) mat.ptr[j+i*mat.cols]);
    printf("\n");
  }
}

void set_matrix_value(matrix* mat, int line, int col, double val) {
  mat->ptr[col+line*mat->cols] = val;
}

matrix add_matrix(matrix mat1, matrix mat2) {
  if ((mat1.lines != mat2.lines) || (mat1.cols != mat2.cols)) {
    printf("Error, matrices have incompatible sizes\n");
    return mat1;
  }
  matrix mat3 = new_matrix(mat1.lines, mat1.cols);
  for (int i=0; i<mat1.lines; i++)
    for (int j=0; j<mat1.cols; j++)
      mat3.ptr[j+i*mat2.cols] = mat1.ptr[j+i*mat1.cols] + mat2.ptr[j+i*mat2.cols];

  return mat3;
}

matrix mult_matrix(matrix mat1, matrix mat2) {
  if (mat1.cols != mat2.lines) {
    printf("Error, matrices have incompatible sizes\n");
    return mat1;
  }
  matrix mat3 = new_matrix(mat1.lines, mat2.cols);
  for (int i=0; i<mat1.lines; i++) {
    for (int j=0; j<mat2.cols; j++) {
      for (int p=0; p<mat1.cols; p++)
        mat3.ptr[j+i*mat2.cols] += mat1.ptr[i+p*mat1.cols]*mat2.ptr[j+p*mat2.cols];
    }
  }
  return mat3;
}





int main() {

  //Addition
  matrix mat1 = new_matrix(3,3);
  matrix mat2 = new_matrix(3,3);
  mat1 = fill_matrix(mat1);
  mat2 = fill_matrix(mat2);
  disp_matrix(mat1);
  disp_matrix(mat2);
  matrix mat3 = add_matrix(mat1, mat2);
  disp_matrix(mat3);

  //Product
  matrix mat4 = new_matrix(3,500);  //3, 5
  matrix mat5 = new_matrix(500,5);  //5, 5
  mat4 = fill_matrix(mat4);
  mat5 = fill_matrix(mat5);
  //disp_matrix(mat4);
  //disp_matrix(mat5);
  matrix mat6 = mult_matrix(mat4, mat5);
  disp_matrix(mat6);

  free(mat1.ptr);
  free(mat2.ptr);
  free(mat3.ptr);
  free(mat4.ptr);
  free(mat5.ptr);
  free(mat6.ptr);
  return 0;
}

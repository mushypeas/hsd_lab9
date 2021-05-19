#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define min(a,b) (((a)<(b))?(a):(b))

int* blockMM(int* m1, int* m2, int row, int col1, int col2) {
  int* res = malloc(sizeof(int) * row * col2);
  for(int i = 0; i < row; ++i) {
    for(int j = 0; j < col1; ++j){    
      res[col1*i+j] = 0;
      for(int k = 0; k < col2; ++k){
        res[col1*i+j] += m1[col1*i+k] * m2[col1*k + j];
      }
    }
  }
  return res;
}

int main(int argc, char const *argv[])
{
  int num_output  = 16;
  int num_input   = 16;
  int num_matrix2 = 16;
  int v_size_     = 4;
  int* weight_mat = malloc(sizeof(int) * num_input * num_output);
  int* input_mat = malloc(sizeof(int) * num_input * num_matrix2);
  int* output = malloc(sizeof(int) * num_output * num_matrix2);

  for (int k = 0; k < num_output; k++)
    for (int n = 0; n < num_input; n++)
      weight_mat[k*num_input + n] = k*10 + n;

  for (int k = 0; k < num_input; k++)
    for (int n = 0; n < num_matrix2; n++)
      input_mat[k*num_matrix2 + n] = k*10 + n;

  for(int m = 0; m<num_output; ++m) {
    for(int n = 0; n<num_input; ++n) {
      printf("%4d ", weight_mat[m*num_input + n]);
    }
    printf("\n");
  }
printf("--------------------------------------------\n");
  for(int m = 0; m<num_input; ++m) {
    for(int n = 0; n<num_matrix2; ++n) {
      printf("%4d ", input_mat[m*num_matrix2 + n]);
    }
    printf("\n");
  }

  // 0) Initialize output vector		
  for(int i = 0; i < num_output*num_matrix2; ++i)
    output[i] = 0;

  for(int i = 0; i < num_output; i += v_size_)
  {
    for(int j = 0; j < num_input; j += v_size_)
    {			
      for(int k = 0; k < num_matrix2; k += v_size_)
      {
        // 0) Initialize input vector
        int block_row = min(v_size_, num_output-i);
        int block_col_1 = min(v_size_, num_input-j);
        int block_col_2 = min(v_size_, num_matrix2-k);
        int* m1 = malloc(sizeof(int) * block_row * block_col_1);
        int* m2 = malloc(sizeof(int) * block_col_1 * block_col_2);

printf("M1\n---------------------\n");
        // 1) Assign a m1
        for (int row = 0; row < block_row; row++) {
          for (int col = 0; col < block_col_1; col++) {
            m1[row*block_col_1 + col] = weight_mat[(i + row)*num_input + (j + col)];
            printf("%4d ", m1[row*block_col_1 + col]);
          }
          printf("\n");
        }

printf("M2\n---------------------\n");
        // 2) Assign a m2
        for (int row = 0; row < block_col_1; row++) {
          for (int col = 0; col < block_col_2; col++) {
            m2[row*block_col_2 + col] = input_mat[(j + row)*num_matrix2 + (k + col)];
            printf("%4d ", m2[row*block_col_2 + col]);
          }
          printf("\n");
        }

        // 3) Call a function `blockMM() to execute Matrix matrix multiplication
        int* ret = blockMM(m1, m2, block_row, block_col_1 ,block_col_2);

        // 4) Accumulate intermediate results
        for(int n = 0; n<block_row; ++n)
        {
        for(int m = 0; m<block_col_2; ++m)
          {
            output[(k + m) + (i + n)*num_matrix2] += ret[n*v_size_ + m];
          }
        }
printf("_out\n---------------------\n");
  for(int n = 0; n<num_output; ++n)
  {
    for(int m = 0; m<num_matrix2; ++m)
    {
      printf("%6d ", output[n*num_matrix2 + m]);
    }
      printf("\n");
  }
        free(m1);
        free(m2);
        free(ret);
      }
    } 
  }
printf("out\n---------------------\n");
  for(int n = 0; n<num_output; ++n)
  {
    for(int m = 0; m<num_matrix2; ++m)
    {
      printf("%6d ", output[n*num_matrix2 + m]);
    }
      printf("\n");
  }
  free(weight_mat);
  free(input_mat);
  free(output);
  return 0;
}
#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[])
{
  int conv_channel = 2;
  int input_channel = 3;
  int conv_height = 2;
  int input_height = 3;
  int conv_width = conv_height;
  int input_width = input_height;
  int new_height = input_height - conv_height + 1;
  int new_width = input_width - conv_width + 1;

  int size [4] = {
    input_channel*input_channel*conv_height*conv_width,
    input_channel*conv_height*conv_width*new_height*new_width,
    conv_channel*input_channel*conv_height*conv_width,
    input_channel*input_height*input_width
  };

  // int* new_weights = malloc(sizeof(int) * size[0]);
  // int* new_inputs = malloc(sizeof(int) * size[1]);
  // int* cnn_weights = malloc(sizeof(int) * size[2]);
  // int* inputs = malloc(sizeof(int) * size[3]);
  int new_weights[input_channel][input_channel*conv_height*conv_width];
  int new_inputs[input_channel*conv_height*conv_width][new_height*new_width];
  int cnn_weights[conv_channel][input_channel][conv_height][conv_width];
  int inputs[input_channel][input_height][input_width];

  for (int i = 0; i < conv_channel; i++)
    for (int j = 0; j < input_channel; j++)
      for (int k = 0; k < conv_height; k++)
        for (int n = 0; n < conv_width; n++)
          cnn_weights[i][j][k][n] = i*1000+j*100+k*10+n;

  for (int j = 0; j < input_channel; j++)
    for (int k = 0; k < input_height; k++)
      for (int n = 0; n < input_width; n++)
        inputs[j][k][n] = j*100+k*10+n;

  printf("---inputs---\n");
  for (int i = 0; i < input_channel; i++) {
    for (int j = 0; j < input_height; j++) {
      for (int k = 0; k < input_width; k++) {
        printf("%4d ", inputs[i][j][k]);
      }
      printf("\n");
    }
    printf("\n");
  }

  // Assign new_weights
  for (int i = 0; i < conv_channel; i++)
    for (int j = 0; j < input_channel; j++)
      for (int k = 0; k < conv_height; k++)
        for (int n = 0; n < conv_width; n++)
          new_weights[i][j*conv_height*conv_width + k*conv_width + n] = cnn_weights[i][j][k][n];
          
  // Assign new_inputs
  for (int ch = 0; ch < input_channel; ch++)
    for (int m_row = 0; m_row < conv_height; m_row++)
      for (int m_col = 0; m_col < conv_width; m_col++)
        for (int row = 0; row < new_height; row++)
          for (int col = 0; col < new_width; col++)
            new_inputs[ch*conv_height*conv_width + m_row*conv_width + m_col][row*new_width + col]
              = inputs[ch][m_row + row][m_col + col];

  printf("---New inputs---\n");
  for (int i = 0; i < input_channel*conv_height*conv_width; i++) {
    for (int j = 0; j < new_height*new_width; j++) {
      printf("%4d ", new_inputs[i][j]);
    }
    printf("\n");
  }

  printf("\n---weights---\n");
  for (int i = 0; i < conv_channel; i++) {
    for (int j = 0; j < input_channel; j++) {
      for (int k = 0; k < conv_height; k++) {
        for (int m = 0; m < conv_width; m++) {
          printf("%4d ", cnn_weights[i][j][k][m]);
        }
        printf("\n");
      }
      printf("\n");
    }
    printf("\n");
  }

  printf("---New weights---\n");
  for (int i = 0; i < conv_channel; i++) {
    for (int j = 0; j < input_channel*conv_height*conv_width; j++) {
      printf("%4d ", new_weights[i][j]);
    }
    printf("\n");
  }

  return 0;
}
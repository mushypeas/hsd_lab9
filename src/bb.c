#include<stdio.h>    
#include<stdlib.h>  
int main(){  
  int num_output = 16;
  int num_input = 8;
  int num_matrix2 = 8   ;
int a[num_output][num_input],b[num_input][num_matrix2],mul[num_output][num_matrix2],i,j,k;    
printf("enter the first matrix =\n");    
for(i=0;i<num_output;i++)    
  {    
  for(j=0;j<num_input;j++)    
  {    
  scanf("%d",&a[i][j]);    
  }    
}    
printf("enter the second matrix element=\n");    
for(i=0;i<num_input;i++)    
{    
for(j=0;j<num_matrix2;j++)    
{    
scanf("%d",&b[i][j]);    
}    
}    
    
printf("multiply of the matrix=\n");    
for(i=0;i<num_output;i++) {    
  for(j=0;j<num_matrix2;j++) {    
    mul[i][j]=0;    
    for(k=0;k<num_input;k++){    
      mul[i][j]+=a[i][k]*b[k][j];    
    }    
  }    
}    
//for printing result    
for(i=0;i<num_output;i++)    
{    
for(j=0;j<num_matrix2;j++)    
{    
printf("%d\t",mul[i][j]);    
}    
printf("\n");    
}    
return 0;  
}  
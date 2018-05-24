#include <stdlib.h>
#include "matmul.h"

#define TILE 16 

Matrix Allocate2ndMatrix(int height, int width, int init);

void matmul( float*, const float*, const float*, unsigned int, unsigned int, unsigned int);

////////////////////////////////////////////////////////////////////////////////
//! C = A * B
//! @param C          result matrix
//! @param A          matrix A 
//! @param B          matrix B
//! @param hA         height of matrix A
//! @param wB         width of matrix B
////////////////////////////////////////////////////////////////////////////////

/* You'll need to modify this function such that matrix B is accessed
 * correctly once you change the memory layout to column-major. */
void matmul(float* C, const float* A, const float* B, unsigned int hA, 
    unsigned int wA, unsigned int wB)
{

  for (unsigned int x = 0; x < hA; x += TILE) {
    for (unsigned int y = 0; y < wB; y += TILE) {
      for (unsigned int z = 0; z < wA; z += TILE) {

        for (unsigned int i = x; i < x + TILE; ++i) {
          for (unsigned int j = y; j < y + TILE; ++j) {
            double sum = 0;
            for (unsigned int k = z; k < z + TILE; ++k) {
              double a = A[i * wA + k];
              double b = B[j * wB + k];
              sum += a * b;
            }
            C[i * wB + j] = (float)sum;
          }
        }

      }
    }
  }
}

// Allocate a matrix of dimensions height*width
Matrix Allocate2ndMatrix(int height, int width)
{
  Matrix M;
  M.width = M.pitch = width;
  M.height = height;
  int size = M.width * M.height;
  M.elements = NULL;

  M.elements = (float*) malloc(size*sizeof(float));

  /* This is a row-major allocation and initialization.
   * You need to modify this function which is only called
   * for Matrix B such that a column-major ordering is
   * performed. */
  //for(unsigned int i = 0; i < M.height * M.width; i++)
  //{
  //  M.elements[i * M.width] = (rand() / (float)RAND_MAX);
  //}
  for (unsigned int i = 0; i < M.height; i++) {
    for (unsigned int j = 0; j < M.width; j++) {
      M.elements[j * M.height + i] = (rand() / (float)RAND_MAX); 
    }
  }
  return M;
}	


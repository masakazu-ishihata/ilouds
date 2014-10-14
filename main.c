#include "main.h"

#define N 20
#define M 3

int main(void)
{
  int i;

  /* 1 -> 2 -> 3,4 */
  ui **A;

  A = (ui **)calloc(N, sizeof(ui *));
  for(i=0; i<N; i++)
    A[i] = (ui *)calloc(M, sizeof(ui));

  A[0][0] = 1; /* 0 -> 1, 2 */
  A[0][1] = 2;
  A[1][0] = 3; /* 1 -> 3 */
  A[2][0] = 4; /* 2 -> 4 */

  ilouds *p = ilouds_new(N, M, A);
  ilouds_show(stdout, p);
  ilouds_free(p);
  for(i=0; i<N; i++) free(A[i]);
  free(A);

  return 0;
}

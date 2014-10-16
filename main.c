#include "main.h"

#define N 5
#define M 3

int main(void)
{
  /* 1 -> 2 -> 3,4 */
  int i;
  ui **A;
  A = (ui **)calloc(N, sizeof(ui *));
  for(i=0; i<N; i++) A[i] = (ui *)calloc(M, sizeof(ui));
  A[0][0] = 1; /* 0 -> 1, 2 */
  A[0][1] = 2;
  A[1][0] = 3; /* 1 -> 3 */
  A[2][0] = 4; /* 2 -> 4 */


  /* test */
  ilouds *p = ilouds_new(N, M, A);
  char bits[256];

  /* export */
  ilouds_show(stdout, p);
  ilouds_export(p, bits);
  ilouds_free(p);

  printf("%s\n", bits);

  /* import */
  p = ilouds_import(bits);
  ilouds_show(stdout, p);
  ilouds_free(p);

  /* free */
  for(i=0; i<N; i++) free(A[i]);
  free(A);

  return 0;
}

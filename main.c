#include "main.h"

#define N 5
#define M 3

int main(void)
{
  /* construct */
  ilouds *l = ilouds_import("louds.txt");
  ilouds_show(stdout, l);
  ilouds_free(l);

  return 0;
}

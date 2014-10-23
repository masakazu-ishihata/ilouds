#include "ilouds.h"

#define BSIZE 256

/*----------------------------------------------------------------------------*/
/* new / free */
/*----------------------------------------------------------------------------*/
/*------------------------------------*/
/* new */
/* _N = # nodes */
/* _M = maximum # children */
/* _A = child list with breadth first order */
/*------------------------------------*/
ilouds *ilouds_new(ui _N, ui _M, ui **_A)
{
  int i, j, k;
  ilouds *_p = (ilouds *)malloc(sizeof(ilouds));

  /* 2N+1 bits are required to represent a tree with N nodes */
  _p->N = _N;
  _p->B = ibary_new(2 * _N + 1);

  /* add root node */
  k = 0;
  ibary_set(_p->B, k++, 1);
  ibary_set(_p->B, k++, 0);

  /* add other nodes with breadth first order */
  for(i=0; i<_N; i++){
    /* set the same # of 1's as # children */
    for(j=0; j<_M; j++)
      if(_A[i][j] > i)
        ibary_set(_p->B, k++, 1);

    /* set 0 */
    ibary_set(_p->B, k++, 0);
  }

  return _p;
}
/*------------------------------------*/
/* free */
/*------------------------------------*/
void ilouds_free(void *_p)
{
  ilouds *_c = (ilouds *)_p;

  if(_c != NULL){
    ibary_free(_c->B);
    free(_c);
  }
}

/*----------------------------------------------------------------------------*/
/* import / export */
/*----------------------------------------------------------------------------*/
/*------------------------------------*/
/* show */
/*------------------------------------*/
void ilouds_show(FILE *_fp, ilouds *_p)
{
  int i, j;

  /* tree structture */
  fprintf(_fp, "ID        |Parent    |Children\n");
  for(i=0; i<_p->N; i++){
    fprintf(_fp, "%10d|", i);
    fprintf(_fp, "%10d|", ilouds_get_parent(_p, i));
    for(j=0; j<ilouds_get_num_children(_p, i); j++)
      fprintf(_fp, "%10d", ilouds_get_child(_p, i, j));
    fprintf(_fp, "\n");
  }
}
/*------------------------------------*/
/* export */
/*------------------------------------*/
void ilouds_export(FILE *_fp, ilouds *_p)
{
  char *bits = ilouds_to_bits(_p);
  fprintf(_fp, "%s", bits);
  free(bits);
}
/*------------------------------------*/
/* import */
/*------------------------------------*/
ilouds *ilouds_import(char const *_file)
{
  FILE *fp = fopen(_file, "r");

  /* get file size */
  int L = 0;
  char buf[BSIZE];
  while(fgets(buf, BSIZE, fp) != NULL)
    L += strlen(buf);

  /* load bits */
  char *bits = (char *)calloc(L + 2, sizeof(char));
  strcpy(bits, "");
  rewind(fp);
  while(fgets(buf, BSIZE, fp) != NULL)
    strcat(bits, buf);

  /* remove \n */
  char *p = strchr(bits, '\n');
  if(p != NULL) *p = '\0';

  /* construct LOUDS */
  ilouds *_p = ilouds_from_bits(bits);

  /* free */
  free(bits);
  fclose(fp);

  return _p;
}


/*----------------------------------------------------------------------------*/
/* converters */
/*----------------------------------------------------------------------------*/
/*------------------------------------*/
/* LOUDS -> Bits */
/*------------------------------------*/
char *ilouds_to_bits(ilouds *_p)
{
  char *_bits = (char *)calloc(2*_p->N+3, sizeof(char));
  ibary_string(_p->B, _bits);
  return _bits;
}
/*------------------------------------*/
/* Bits -> LOUDS */
/*------------------------------------*/
ilouds *ilouds_from_bits(const char *_bits)
{
  ilouds *_p = (ilouds *)malloc(sizeof(ilouds));
  int L = strlen(_bits);
  _p->B = ibary_new(L);
  _p->N = (L-1) / 2;

  /* load structure */
  int i;
  for(i=0; i<L; i++)
    ibary_set(_p->B, i, _bits[L-i-1] == '0' ? 0 : 1);

  return _p;
}


/*----------------------------------------------------------------------------*/
/* accessors */
/*----------------------------------------------------------------------------*/
/*------------------------------------*/
/* id of _i-th node */
/* = id of _i-th "1" in B */
/*------------------------------------*/
int ilouds_get_index(ilouds *_p, ui _i)
{
  return ibary_select(_p->B, 1, _i);
}
/*------------------------------------*/
/* head of _i = index of the first child of _i */
/*------------------------------------*/
int ilouds_get_head(ilouds *_p, ui _i)
{
  return ibary_select(_p->B, 0, _i) + 1;
}
/*------------------------------------*/
/* ID of _i-th node's parent */
/*------------------------------------*/
int ilouds_get_parent(ilouds *_p, ui _i)
{
  /* skip if no such node */
  if(_i >= ibary_rank(_p->B, 1, 2*_p->N)) return -1;

  /* id of (_i+i)-th "1" in B */
  int n = ibary_select(_p->B, 1, _i);

  /* count # 0's before n in B[0, n) */
  int m = ibary_rank(_p->B, 0, n);

  return m-1;
}
/*------------------------------------*/
/* ID of _i-th node's _j-th child */
/*------------------------------------*/
int ilouds_get_child(ilouds *_p, ui _i, ui _j)
{
  /* skip if no such node */
  if(_j >= ilouds_get_num_children(_p, _i)) return -1;

  /* id of "1" representing the _j-th child of _i */
  int n = ilouds_get_head(_p, _i) + _j;

  /* # 1's before n = original ID of n */
  int m = ibary_rank(_p->B, 1, n);
  return m-1;
}
/*------------------------------------*/
/* # of _i-th node's children */
/*------------------------------------*/
int ilouds_get_num_children(ilouds *_p, ui _i)
{
  return ilouds_get_head(_p, _i+1) - ilouds_get_head(_p, _i) - 1;
}
/*------------------------------------*/
/* # of nodes */
/*------------------------------------*/
int ilouds_get_size(ilouds *_p)
{
  return _p->N;
}

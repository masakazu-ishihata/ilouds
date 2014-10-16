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

  /* 2N bits are required to represent a tree with N nodes */
  _p->N = _N;
  _p->B = ibary_new(2 * _N);

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

  /* bit array */
  ibary_show(_fp, _p->B);

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
void ilouds_export(ilouds *_p, char *_bits)
{
  ibary_string(_p->B, _bits);
}
/*------------------------------------*/
/* import */
/*------------------------------------*/
ilouds *ilouds_import(const char *_bits)
{
  ilouds *_p = (ilouds *)malloc(sizeof(ilouds));
  _p->N = strlen(_bits) / 2;
  _p->B = ibary_new(_p->N * 2);

  /* load structure */
  int i;
  for(i=0; i<2*_p->N; i++)
    ibary_set(_p->B, i, _bits[2*_p->N-i-1] == '0' ? 0 : 1);

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
  return ibary_select(_p->B, 1, _i+1);
}
/*------------------------------------*/
/* head of _i = index of the first child of _i */
/*------------------------------------*/
int ilouds_get_head(ilouds *_p, ui _i)
{
  return ibary_select(_p->B, 0, _i+1) + 1;
}
/*------------------------------------*/
/* ID of _i-th node's parent */
/*------------------------------------*/
int ilouds_get_parent(ilouds *_p, ui _i)
{
  /* skip if no such node */
  if(_i >= ibary_rank(_p->B, 1, 2*_p->N)) return -1;

  /* id of "1" representing _i-th node in B */
  int n = ibary_select(_p->B, 1, _i+1);

  /* count # 0's before n in B */
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

#ifndef _ILOUDS_H_
#define _ILOUDS_H_

/*------------------------------------*/
/* include */
/*------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <ibary.h>

/*------------------------------------*/
/* typedef */
/*------------------------------------*/
typedef unsigned int ui;

/*------------------------------------*/
/* ilouds */
/*------------------------------------*/
typedef struct ILOUDS
{
  ui     N; /* # nodes */
  ibary *B; /* tree */
  ui    *L; /* labels */
} ilouds;
/* new / free / show */
ilouds *ilouds_new(ui _N, ui _M, ui **_A);
void ilouds_free(void *_p);
void ilouds_show(FILE *_fp, ilouds *_p);

/* accessors */
int ilouds_get_index(ilouds *_p, ui _i);
int ilouds_get_head(ilouds *_p, ui _i);
int ilouds_get_parent(ilouds *_p, ui _i);
int ilouds_get_child(ilouds *_p, ui _i, ui _j);
int ilouds_get_num_children(ilouds *_p, ui _i);
void ilouds_set_label(ilouds *_p, ui _i, ui _l);


#endif

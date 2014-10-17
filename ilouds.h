#ifndef _ILOUDS_H_
#define _ILOUDS_H_

/*------------------------------------*/
/* include */
/*------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
} ilouds;
/* new / free */
ilouds *ilouds_new_matrix(ui _N, ui _M, ui **_A);
void ilouds_free(void *_p);

/* import / export */
void ilouds_show(FILE *_fp, ilouds *_p);
void ilouds_export(FILE *_fp, ilouds *_p);
ilouds *ilouds_import(char const *_file);

/* converters */
char *ilouds_to_bits(ilouds *_p);
ilouds *ilouds_from_bits(const char *_bits);

/* accessors */
int ilouds_get_index(ilouds *_p, ui _i);
int ilouds_get_head(ilouds *_p, ui _i);
int ilouds_get_parent(ilouds *_p, ui _i);
int ilouds_get_child(ilouds *_p, ui _i, ui _j);
int ilouds_get_num_children(ilouds *_p, ui _i);
int ilouds_get_size(ilouds *_p);

#endif

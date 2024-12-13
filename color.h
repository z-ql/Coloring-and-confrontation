#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include "header.h"
int isSafe(int v, int graph[Maxregions][Maxregions], struct tjMap *tmap, int c);
int colorateMap(int graph[Maxregions][Maxregions], int m, struct tjMap *tmap, int v);

#endif // COLOR_H_INCLUDED

#ifndef LOAD_H_INCLUDED
#define LOAD_H_INCLUDED

#include "header.h"
void dfs1(struct tjMap *tmap, int x, int y, char letter, int id);
void dfs2(struct tjMap *tmap, int x, int y, int id);
void loadNewMap(char str0[]);

#endif // LOAD_H_INCLUDED

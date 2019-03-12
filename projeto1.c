#include <stdio.h>
#include <stdlib.h>
#include "ROUTER.h"

struct router{
    int N, M;
    int **adj;
};

Router ROUTERinit(int N){
    Router R = malloc(sizeof(struct router));
    R -> N = N;
    R -> M = 0;
    R -> adj = MATRIXinit(N,N,0);
    return R;
}


int main(int argc, char const *argv[])
{
    int router[N][M];
    FILE *f;
    f =fopen(filename, "r");
    if ((N < 2) && (M < 1)){ fprintf(stderr,"Invalid number");}
    return 0;
}

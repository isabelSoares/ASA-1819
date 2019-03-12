#include <stdio.h>
#include <stdlib.h>
#include "ROUTER.h"

struct router{
    int N, M;
    int **adj;
};

Router ROUTERinit(int N, int M){
    Router R = malloc(sizeof(struct router));
    R -> N = N;
    R -> M = M;
    R -> adj = MATRIXinit(N,N,0);
    return R;
}


int main(int argc, char const *argv[])
{
    int N,M;
    


    scanf("%d", &N);
    scanf("%d", &M);
    if ((N < 2) && (M < 1)){ fprintf(stderr,"Invalid number");}
    ROUTERinit(N,M);

    return 0;
}

int **MATRIXinit(int lines, int columns, int value){
    int matrix [lines][columns];
    memset(matrix, 0, sizeof(matrix[0][0]) * lines * columns);
    return matrix;
}

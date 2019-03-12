typedef struct{
    int N;
    int M;
}Router;

Router ROUTER(int x, int y);
typedef  struct network *Network;

Network NETWORKinit(int, int);
link InsertBegin(int, link);
void NETWORKinsertM(Network, int, int);
int** MATRIXinit(int, int, int);
void NETWORKinsert(Network N, int r1, int r2);
// ptrace nao permitido, execute para arrumar:
// sudo echo 0 > /proc/sys/kernel/yama/ptrace_scope

#include <iostream>
#include "ga.h"
#include <fstream>

#define N 15
#define nObjective 12
#define nSalesman 3
#define IN 0xFFFFFF
using namespace std;


int m[N][N] = {{0,	7,	7,	5,	14,	10,	15,	18,	20,	17,	14,	12,	3,	3,	IN},
               {7,	0,	5,	3,	17	,3,10,	13,	15,	12,	10,	8,	4,	4,	IN},
                {7,	5,	0,	1,	15	,20,25,	22,	28,	25,	23,	22,	4,	4,	IN},
                {5,	3,	1,	0,	13	,18,23,	20,	26,	23,	21	,20,	2,	2,	IN},
                {14,	17,	15,	13,	0	,18,22,	17,	20,	15,	13	,16	,11,	11,	IN},
                {10	,3	,20,18,	18	,0,	7,	7,	8,	8,	9,	11,	IN,	IN,	4},
                {15	,10	,25	,23,22	,7	,0,	6,	7,	7,	8,	10,	IN,	IN,	3},
                {18	,13	,22	,20	,17	,7	,6,0,	7,	7,	8,	11,	IN,	IN,	3},
                {20	,15	,28	,26	,20	,8	,7,	7,	0,	8,	9,	11,	IN,	IN,	4},
                {17,	12	,25	,23	,15	,8	,7,	7,	8,	0,	9,	11,	IN,	IN,	4},
               { 14	,10	,23	,21	,13	,9	,8,	8,	9,	9,	0,	12,	IN,	IN,	5},
               { 12,	8	,22	,20	,16	,11	,10,	11,	11,	11,	12,	0	,IN	,IN,	7},
               { 3,	4	,4	,2	,11	,IN	,IN,	IN,	IN,	IN,	IN,	IN,	0,	IN	,IN},
               { 3,	4	,4	,2	,11	,IN	,IN,	IN,	IN,	IN,	IN,	IN,	IN,	0,IN},
               { IN,	IN	,IN	,IN	,IN	,4	,3,	3,	4,	4,	5,	7,	IN ,	IN,	0}

                 };

int **cities;


int objectives[nObjective] = {0,1,2,3,4,5,6,7,8,9,10,11};
int depot[nSalesman] = {12,13,14};

/*
digraph finite_state_machine {
    rankdir=LR;
    size="8,5"
    node [shape = doublecircle]; LR_0 LR_3 LR_4 LR_8;
    node [shape = circle];
    LR_0 -> LR_2 [ label = "SS(B)" ];
    LR_0 -> LR_1 [ label = "SS(S)" ];
    LR_1 -> LR_3 [ label = "S($end)" ];
    LR_2 -> LR_6 [ label = "SS(b)" ];
    LR_2 -> LR_5 [ label = "SS(a)" ];
    LR_2 -> LR_4 [ label = "S(A)" ];
    LR_5 -> LR_7 [ label = "S(b)" ];
    LR_5 -> LR_5 [ label = "S(a)" ];
    LR_6 -> LR_6 [ label = "S(b)" ];
    LR_6 -> LR_5 [ label = "S(a)" ];
    LR_7 -> LR_8 [ label = "S(b)" ];
    LR_7 -> LR_5 [ label = "S(a)" ];
    LR_8 -> LR_6 [ label = "S(b)" ];
    LR_8 -> LR_5 [ label = "S(a)" ];
}

 */

void createDigraph()
{
    int j,i;
    ofstream myfile;
    myfile.open ("graph.gv");
    myfile << "digraph finite_state_machine {\n";
    myfile << "size=\"8,5\";\n";
    myfile << "node[shape = circle]; \n";
    for(i=0;i<N;++i)
        for(j=0;j<N;++j)
            if(i!=j &&  cities[i][j] != IN)
                myfile << i << " -> " << j << " [ label = \"" << cities[i][j] << "\" ];\n";
    myfile << "}";
    myfile.close();
}

int main()
{
    srand(time(NULL));

    int i,j;
    cities = (int**) malloc(sizeof(int*) * N);
    for(i=0;i<N;++i)
        cities[i] = (int*) malloc(sizeof(int) * N);
    for(i=0;i<N;++i)
        for(j=0;j<N;++j)
            if(i!=j)
                cities[i][j] = m[i][j];
            else
                cities[i][j] = 0;

    createDigraph();
    GA *a = new GA(nObjective, nSalesman,0.5f,20000,depot,nObjective,objectives,N,cities);
    Chromosome *x = a->evolution();

    cout << endl << "------------------------------" << endl;
    /*for(i=0;i<N;++i)
     {
        for(j=0;j<N;++j)
        {
            cout << cities[i][j] << " ";
        }
        cout << endl;
    }*/
    cout << endl;
    for(i=0; i<nObjective+nSalesman;++i) {
        cout <<  x->Genes[i] << " ";
    }
    cout << "\n" << "Score: " << x->Score << endl;
    cout << "Depositos: ";
    for(i=0; i<nSalesman;++i) {
        cout <<  depot[i] << " ";
    }
    cout << endl;
    cout << "Rota: ";
    for(i=0; i<x->route->size();++i) {
        cout <<  x->route->at(i) << " ";
    }
    cout << endl;
    return 0;
}


// ptrace nao permitido, execute para arrumar:
// sudo echo 0 > /proc/sys/kernel/yama/ptrace_scope

#include <iostream>
#include "ga.h"
#include <fstream>

#define N 1000
#define nObjective 16
#define nSalesman 8
#define IN 0xFFFFFF
using namespace std;

/*
int m[N][N] = { {0,IN,IN,3,4,4,2,11,IN,IN,IN,IN,IN,IN,IN},
                {0,IN,IN,3,4,4,2,11,IN,IN,IN,IN,IN,IN,IN},
                {1,1,0,1,1,1,1,1},
                {1,1,1,0,1,1,1,1},
                {1,1,1,1,0,1,1,1},
                {1,1,1,1,1,0,1,1},
                {1,1,1,1,1,1,0,1},
                {1,1,1,1,1,1,1,0}
                 };
*/
int **cities;


int objectives[nObjective] = {2,4,6,7,8, 10,200,302,120,21, 40,800,700,750,850 ,128};
int depot[nSalesman] = {3,5,655,9,14,30,45,765};

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
                cities[i][j] = rand()%200+3;
            else
                cities[i][j] = 0;

    createDigraph();
    GA *a = new GA(nObjective, nSalesman,0.5f,100,depot,nObjective,objectives,N,cities);
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


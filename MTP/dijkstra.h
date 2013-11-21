#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#define INF 0xFFFFFF

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

class Dijkstra{

public:
    int N;
    int inicio, dest;
    int **visitados;
    float **caminhos;
    float **originalCaminhos;
    int menor(int ind, int *menor)
    {
        int i,vertice = 0;
        *menor = INF;
        for(i = 0; i < N; ++i)

            if(*menor > caminhos[ind][i] && caminhos[ind][i] != 0)
            {
                *menor =  caminhos[ind][i];
                vertice = i;
            }
        //printf("vertice: %d\n", vertice);
        return vertice;

    }
    //max = até onde se deve olhar no vetor
    int jaVisitado(int ind, int max)
    {
        int i;
        for(i = 0; i <= max-1; ++i)
            if(visitados[i][0] == ind)
                return 1;
        return 0;
    }

    Dijkstra(int n, float **caminhos)
    {
        this->N = n;
        this->caminhos = caminhos;
        int i,j;

        this->visitados = (int**) malloc(sizeof(int*) * (n+n));
        for(i=0;i<n+n;++i)
            this->visitados[i] = (int*) malloc(sizeof(int) * 2);
        this->originalCaminhos = (float**) malloc(sizeof(float*) * n);
        for(i=0;i<n;++i)
            this->originalCaminhos[i] = (float*) malloc(sizeof(float) * n);
        for(i=0;i<n;++i)
            for(j=0;j<n;++j)
                this->originalCaminhos[i][j] = this->caminhos[i][j];


    }
    // lv : indice do caminho
    // max: numero de cidades
    float Distance(int *tour,int lv, int max, std::vector<float> *route)
    {
        if(lv == 0 && max == 0)
            return 0;

        float custo = 0,re;
        int i,j=0;

        visitados[0][0] = tour[lv];
        visitados[0][1] = 0;
        for(i=0;i<N;++i)
            for(j=0;j<N;++j)
                this->caminhos[i][j] = this->originalCaminhos[i][j];
        j = i = 0;
        do{

            visitados[j+1][0] = menor(visitados[j][0],&visitados[j][1]);
            j++;
            // -1 : Significa que não encontrou outro caminho a nao ser o loop
            if(visitados[j][1] == INF-1)
            {return -1;}
            //verifica se esta em um loop
            if(jaVisitado(visitados[j][0],j))
            {
                //Apaga o loop
                i = visitados[j-1][0];
                //evita o loop colocando um valor alto para nao repetir o loop
                caminhos[i][visitados[j][0]] = INF-1;
                j-=2;
            }
            if(tour[lv+1] == visitados[j][0])
            {
                for(i = 0;i<=j;++i)
                {
                    //printf("%d ", visitados[i][0]);
                    custo += visitados[i][1];
                    route->push_back(visitados[i][0]);
                }
                if(lv+1 == max-1)
                {
                    route->push_back(-1);
                    return custo;
                }
                re = this->Distance(tour, lv+1,max,route);
                if(re != -1)
                    return custo + re;
                else
                    return -1;
            }
        }while(1);
    }
};
#endif // DIJKSTRA_H

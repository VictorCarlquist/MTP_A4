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
    int **visitadosCopy;
    int **visitados;
    int **caminhos;

    int min(int a, int b)
    {
        if(a>b)
            return b;
        else
            return a;
    }

    int minLinha()
    {
        int i = 0;
        int vertice = 0;
        int menor = INF;
        for(i=0;i<N;++i)
        {
            if(visitados[i][0] < menor && visitados[i][1] == 0 && visitados[i][0] != 0)
            {
                vertice = i;
                menor = visitados[i][0];
            }
        }
        return vertice;
    }

    int isExist(int peso)
    {
        int i = 0;
        for(i=0;i<N;++i)
        {
            if(visitadosCopy[i][0] == peso)
                return 1;
        }
        return 0;
    }

    Dijkstra(int n, int **caminhos)
    {
        this->N = n;
        this->caminhos = caminhos;
        int i,j;

        this->visitados = (int**) malloc(sizeof(int*) * (n));
        for(i=0;i<n;++i)
            this->visitados[i] = (int*) malloc(sizeof(int) * 2);
        this->visitadosCopy = (int**) malloc(sizeof(int*) * (n));
        for(i=0;i<n;++i)
            this->visitadosCopy[i] = (int*) malloc(sizeof(int) * 2);

    }
    // lv : indice do caminho
    // max: numero de cidades
    int Distance(int *tour,int lv, int max, std::vector<int> (*route))
    {
        if(lv + 1 == max)
        {
            route->push_back(-1);
            return 0;
        }
        int i,j=0,k=1;

        for(i=1;i<N;++i)
        {
            visitados[i][0] = INF;
            visitados[i][1] = 0;
        }
        visitados[tour[lv]][0] = 0;
        visitados[tour[lv]][1] = 1; // permanente
        route->push_back(tour[lv]);


        i = 0;
        j = tour[lv];

        do{

            for(i=0;i<N;++i)
                visitadosCopy[i][0] = visitados[i][0];
            for(i=0;i<N;++i)
                visitados[i][0] = min(visitados[i][0], visitados[j][0] + caminhos[j][i]);
            route->push_back(minLinha());

            j = route->back();
            visitados[j][1] = 1;


        }while(route->back() != tour[lv+1]);
        if(isExist(visitados[route->back()][0]))
        {
            route->erase(route->end()-2);
           /* for(i=0;i<route->size();i++)
                    std::cout << (*route)[i] ;*/
        }/*else
            for(i=0;i<route->size();i++)
                std::cout  << (*route)[i];
        */
        if(visitados[(*route)[k]][0] == 0) // Nao existe caminho!
            return INF/2;
        return visitados[(*route)[k]][0] + this->Distance(tour, lv+1,max,route);

    }
};
#endif // DIJKSTRA_H

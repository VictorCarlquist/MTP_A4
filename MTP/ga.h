#ifndef GA_H
#define GA_H

/**
 * <nSalesman>  Número de viajantes
 */

#include "dijkstra.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>



class Chromosome
{
    // two-part chromosome
    // n = 6, m = 3
    // xxxxxx|xxx
public:
    int *Genes;
    float Score;
    int nm;
    std::vector<int> *route;
    //n : numero de objetivos que os caixeiros devem passar
    //m : numero de caixeiros
    //nm: n+m
    Chromosome(int nm)
    {
        this->nm = nm;
        this->Genes = (int *) malloc(sizeof(int) * nm);

    }
    //n : numero de objetivos que os caixeiros devem passar
    //m : numero de caixeiros
    //nm: n+m
    Chromosome(int nm,int* Genes)
    {
        this->Genes = (int *) malloc(sizeof(int) * nm);
        this->Genes = Genes;
    }

};

class GA
{
    public:
        float RateMutation;
        std::vector<Chromosome*> Population;

        int nNode;
        int nSalesman;
        int *depotSalesman; //depositos inciais dos caixeiros
        int *objectives;  //devem ser visitados
        int nObjectives;
        int nGeneration;
        int TotalCities;

        Dijkstra *dijkstra;
        

        GA(int nNode, int nSalesman, float RateMutation, int nGeneration,int *depotSalesman,int nObjectives, int *objectives, int totalCities, int **cities)
        {
            srand(time(NULL));
            this->Population.reserve(10000);
            this->RateMutation = RateMutation;
            this->nNode = nNode;//objetivos
            this->nSalesman = nSalesman;

            this->depotSalesman = (int *) malloc(sizeof(int) * nSalesman);
            this->depotSalesman = depotSalesman; //pontos iniciais

            this->objectives = objectives;
            this->nObjectives = nObjectives;

            this->nGeneration = nGeneration;

			this->TotalCities = totalCities;
            dijkstra = new Dijkstra(totalCities,cities);


            // TESTE: assumindo que o total this->nNode+this->nSalesman =  6
            // cria os caminhos |0|1|2|3|4|5(|)2|2|
            int i;
            Chromosome *n = new Chromosome(this->nNode+this->nSalesman);
            for(i=0;i<this->nObjectives;i++)
                n->Genes[i]=this->objectives[i];
            for(i=this->nNode;i<this->nNode+this->nSalesman;++i)
                n->Genes[i]   = 2;


            this->addChromosome(n);
            for(i=0; i<this->nNode+this->nSalesman;++i)
                std::cout <<  n->Genes[i] << " ";
            std::cout << std::endl;

            // reverse
            // cria os caminhos |3|2|1|0(|)2|2|

            n = new Chromosome(this->nNode+this->nSalesman);
            for(i=0;i<this->nObjectives;i++)
                n->Genes[i]=this->objectives[this->nObjectives-1-i];
            for(i=this->nNode;i<this->nNode+this->nSalesman;++i)
                n->Genes[i]   = 2;
            for(i=0; i<this->nNode+this->nSalesman;++i)
                std::cout <<  n->Genes[i] << " ";
            std::cout << std::endl;

            this->addChromosome(n);




        }
        Chromosome* evolution()
        {
            int i,j;
            Chromosome *c = this->Population.back();
            for(i = 0;i<this->nGeneration;++i)
            {
                c = this->crossover(c);
                this->mutation(c);
                /*for(j=0; j<this->nNode+this->nSalesman;++j)
                    std::cout <<  c->Genes[j] << " " ;
                */
                std::cout << "Score: " << c->Score << std::endl;

            }
            return this->Population[0];

        }

        bool isExist(int s, int *Genes)
        {
            int i = 0;
            for(i = 0; i< this->nNode; ++i)
                if(s == Genes[i])
                    return true;
           return false;
        }
		
        void mutation(Chromosome *c)
        {
            int x,y,z;
            float r =  ((double) rand() / (RAND_MAX));
            if(this->RateMutation > r)
            {
                do{
                    x = rand() % (this->nNode);
                    y = rand() % (this->nNode);

                }while(x == y);

                z = c->Genes[x];
                c->Genes[x] = c->Genes[y];
                c->Genes[y] = z;
            }
        }

        static bool cmd(const Chromosome  *s1, const Chromosome  *s2)
        {
           return s1->Score < s2->Score;
        }
        void addChromosome(Chromosome *c)
        {
            this->evaluate(c);
            if(c->Score > 0)
                this->Population.push_back(c);

            std::sort(this->Population.begin(),this->Population.end(),cmd);

        }
        void evaluate(Chromosome *c)
        {
            c->Score = this->score(c->Genes,c);
        }
        float score(int * genes,Chromosome *c)
        {
            float score = 0;
            int i = 0,w=0;
            int j = genes[this->nNode];
            std::vector<std::deque<int> > p;
            std::deque<int> k;
            p.reserve(100);
            i=0;
            do
            {
                //std::cout << genes[i] << std::endl;
                if(k.size() < j)
                {
                    k.push_back(genes[i]);
                    i++;
                }else{
                    //coloca um deposito como inicio e fim do percurso
                    k.push_front(this->depotSalesman[w]);
                    k.push_back(this->depotSalesman[w]);

                    w++;
                    p.push_back(k);
                    k.clear();
                    j = genes[this->nNode+ p.size()];
                }
            }while(i<this->nNode);
            //coloca um deposito como inicio e fim do percurso
            k.push_front(this->depotSalesman[w]);
            k.push_back(this->depotSalesman[w]);

            p.push_back(k);
            k.clear();

            std::vector<int> *route = new std::vector<int>();
            route->reserve(2000);


            for(i = 0;i<p.size();++i)
            {
                score+= dijkstra->Distance(&p[i][0],0,p[i].size(),route);
            }
            c->route = route;

           return score;
        }
        // partially-mapped crossover
        void pmx(Chromosome *g1, Chromosome *g2, Chromosome *f1, Chromosome *f2)
        {
            int x = rand() % (this->nNode - 3 + 1) + 3;
            int i;

            for(i = 0; i<this->nNode; ++i)
                g1->Genes[i] = -1;
            for(i = 0; i<this->nNode; ++i)
                g2->Genes[i] = -1;

            for(i = x;i<x+3;++i)
            {
                g1->Genes[i] = f2->Genes[i];
                g2->Genes[i] = f1->Genes[i];
            }

            //Evita que as cidades sejam repetidas dentro do cromossoma
            for(i = 0; i<this->nNode; ++i)
            {
                if(!this->isExist(f1->Genes[i],g1->Genes))
                {
                    if(g1->Genes[i] == -1)
                        g1->Genes[i] = f1->Genes[i];
                }else{
                    x = 0;
                    while(this->isExist(this->objectives[x],g1->Genes) && x <= this->nObjectives) x++;
                    if(x < this->nObjectives)
                    {
                        g1->Genes[i] = this->objectives[x];
                        continue;
                    }
                    x = 0;
                    while(this->isExist(this->depotSalesman[x],g1->Genes) && x <= this->nSalesman) x++;
                    g1->Genes[i] = this->depotSalesman[x];
                }
            }
            for(i=this->nNode;i<this->nNode+this->nSalesman;++i)
                g1->Genes[i] = f1->Genes[i];
            //Evita que as cidades sejam repetidas dentro do cromossoma
            for(i = 0; i<(this->nNode+this->nSalesman); ++i)
            {
                if(!this->isExist(f2->Genes[i],g2->Genes))
                {
                    if(g2->Genes[i] == -1)
                        g2->Genes[i] = f2->Genes[i];
                }else{
                    x = 0;
                    while(this->isExist(this->objectives[x],g2->Genes) && x <= this->nObjectives) x++;
                    if(x < this->nObjectives)
                    {
                        g2->Genes[i] = this->objectives[x];
                        continue;
                    }
                    x = 0;
                    while(this->isExist(this->depotSalesman[x],g2->Genes) && x <= this->nSalesman) x++;
                    g2->Genes[i] = this->depotSalesman[x];
                }
            }
            for(i=this->nNode;i<this->nNode+this->nSalesman;++i)
                g2->Genes[i] = f2->Genes[i];



        }
        Chromosome* raffleChromosome()
        {
            int x = rand() % this->Population.size();
        	return this->Population[x];
        } 
        Chromosome* crossover(Chromosome *a)
        {
            //cruza com tres genes
            Chromosome *f1 = this->raffleChromosome();

            Chromosome *new1 = new Chromosome(this->nNode+this->nSalesman);
            Chromosome *new2 = new Chromosome(this->nNode+this->nSalesman);

            this->pmx(new1, new2, a,f1);

            this->addChromosome(new1);
            this->addChromosome(new2);

            if(new1->Score > new2->Score)
            {
                if(new2->Score < a->Score){
                    return new2;
                }else
                    return a;
            }else
                if(new1->Score < a->Score){
                    return new1;
                }else
                    return a;
        }
};

#endif // GA_H

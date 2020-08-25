#include "TSPpath.h"
#include "mpi.h"

#ifndef __GeneticTSP__
#define __GeneticTSP__

class Chromo: public Path {

    private:
    double *MutProb;	//mutations' probabilities

    public:
    //constructors
    Chromo();
    Chromo(DataVett* pos, Random* rnd, int ichr, int rank);
    //destructor
    ~Chromo(){delete[] MutProb;}
    //functions
    Chromo& operator=(const Chromo& chr);//define = operator for Chromo
    void Mutation();			//try all possible mutations

};


class Population {

    private:
    int Ncit,GenMax;	//#cities to visit, min #gen without improving to end
    int Nmigr;		//each Nmigr migration between cores (parallel code)
    int Nchr,TotD;	//#chromosomes (better if even), Ncit*Nspace
    bool Square;	//if 1 cities in a square, else on a circumference
    string* Loc;	//"square" or "circ", usefull for output file
    double Box;		//square 2*side or circumference radius
    Random* Rnd;
    DataVett* Pos;	//cities positions
    Chromo** Chr;	//pointer to population's firts chromosome's pointer
    Chromo S[2];	//sons generated by crossover
    double CrossProb;	//crossover probability
    double MinLoss;	//Loss of the shortest path visited
    int ParSize,ParRank;//size and rank for parallel code

    //internal functions
    void Crossover(int,int);	//crossover operator
    int Selection() const;	//sort one parent (less cost frequently)
    void Ordering();		//fitness based population ordering
    void Migration(int);	//migration between cores (parallel code)
    void WriteLength(int) const;//write 1-st path, 1-st half mean lenghts
    void WriteEnd();		//write final path in default file
    
    public:
    //constructors
    Population();
    Population(Random* rnd);
    Population(Random* rnd, int size, int rank);
    void CommConstr();		//constructors' common operations
    //destructor
    ~Population();
    //values access
    int GetNcit() const		{return Ncit;}
    int GetNchr() const		{return Nchr;}
    Chromo* GetChromo(int i)	{return Chr[i];}
    //functions
    void Evolution();		//Genetic evolution

};

#endif

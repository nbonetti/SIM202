#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <random>
using namespace std;

// fonction qui renvoie un nombre aléatoire entre k et n de manière uniforme
int unif_rand(int k, int n);

//=========================================================================================================================
//                                              CLASSE INDIVIDU
//=========================================================================================================================

class Individu
{
private:
    vector<double> genes;
    double poid_chemin;
    int n;

public:
    //=================================================================
    //   fonctions virtuelles à définir dans la classe fille
    //=================================================================

    // fonction qui affiche le chemin
    virtual void print(ostream &out) const = 0;

    // fonction qui calcule la distance totale du chemin
    virtual double poids() const = 0;

    //=================================================================
    //         fonction propre à la classe Individu
    //=================================================================

    Individu *flip();
    Individu *mutation();
    Individu *crossover(const Individu &partner);
};

//=========================================================================================================================
//                                           CLASSE ENFANT AKA CHEMIN
//=========================================================================================================================

class Chemin : public Individu
{
private:
    vector<double> genes;
    double poid_chemin;
};

//=========================================================================================================================
//                                                CLASSE POPULATION
//=========================================================================================================================

class population
{
public:
    vector<Individu *> Individus;
};
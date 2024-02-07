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
protected:
    vector<double> genes;
    int nombreGenes;

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

    Individu *mutationPermutation();
    Individu *mutationAleatoire();
    Individu *hybridation(const Individu &partenaire);
};

//=========================================================================================================================
//                                           CLASSE CREATEUR
//=========================================================================================================================

enum class IndividuType
{
    Chemin
};

class IndividuCreator
{
public:
    Individu *FactoryMethod();
    void CreateIndividu(IndividuType type);
    IndividuType type;
};

//=========================================================================================================================
//                                           CLASSE ENFANT AKA CHEMIN
//=========================================================================================================================

class Chemin : public Individu
{

public:
    void print(ostream &out) const;
    double poids() const;
};

//=========================================================================================================================
//                                                CLASSE POPULATION
//=========================================================================================================================

class Population
{
public:
    vector<Individu *> Individus;
};

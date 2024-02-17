#ifndef ALGOGENETIQUE_HPP
#define ALGOGENETIQUE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <random>

using namespace std;

// permet de faire la liste de toutes les classes d'individu possibles
enum IndividuType
{
    NoneType,
    CheminType
};

// fonction qui renvoie un nombre aléatoire entre k et n de manière uniforme
int unif_rand(int k, int n);

//=========================================================================================================================
//                                              CLASSE INDIVIDU
//=========================================================================================================================

class Individu
{

public:
    vector<double> genes;
    int nombreGenes;

    //=================================================================
    //   fonctions virtuelles à définir dans la classe fille
    //=================================================================
    Individu() : type(IndividuType::NoneType){};
    Individu(vector<double> premiersGenes)
    {
        genes = premiersGenes;
        nombreGenes = premiersGenes.size();
        type = IndividuType::NoneType;
    }
    // fonction qui affiche le chemin//les gènes
    virtual void print(ostream &out) const = 0;

    // fonction qui calcule la distance totale du chemin
    virtual double poids() const = 0;

    virtual ~Individu(){};

    // permet de remplir les gènes d'un individu donné + récup la taille du vecteur de gènes
    void setGenes(vector<double> nouveauxGenes)
    {
        genes = nouveauxGenes;
        nombreGenes = nouveauxGenes.size();
    }

    //=================================================================
    //         fonction propre à la classe Individu
    //=================================================================

    Individu *mutationPermutation();
    Individu *mutationAleatoire();

    IndividuType type;
};

//=========================================================================================================================
//                                                CLASSE POPULATION
//=========================================================================================================================

class Population
{
protected:
    vector<Individu *> individus;
    int taille_Population;

public:
    // constructeur de population d'individu*
    Population(vector<Individu *> premiersIndividus)
    {
        individus = premiersIndividus;
        taille_Population = individus.size();
    }

    // surcharge d'opérateur qui permet de concatener deux populations
    Population operator+(const Population &Pop2);
    // virtual void print(ostream &out) = 0;
};

// permet de créer deux enfants à partir de deux parents + argument de pointeur de la fonction de factory methode cf Factory.hpp
Population hybridation(const Individu &parent_1, const Individu &parent_2, Individu *(*pointeur_FactoryMethod)(IndividuType type));

#endif

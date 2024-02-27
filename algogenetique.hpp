#ifndef ALGOGENETIQUE_HPP
#define ALGOGENETIQUE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <random>
#include <random>

// Fonction pour générer un nombre aléatoire entre k et n de manière uniforme
int unif_rand(int k, int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(k, n);
    return dis(gen);
}

using namespace std;

// permet de faire la liste de toutes les classes d'individu possibles
enum IndividuType
{
    NoneType,
    CheminType
};

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

    Individu *mutationPermutation()
    {
        if (nombreGenes <= 2)
        {
            cout << "mutation impossible car <=2";
            exit(-1);
        }

        // deux indices alétoirement
        int l = unif_rand(1, nombreGenes - 1);
        int k = unif_rand(0, nombreGenes - 2);

        // échange des valeurs
        int gene_k = genes[k];
        genes[k] = genes[k + 1];
        genes[k + 1] = gene_k;

        int gene_l = genes[l];
        genes[l] = genes[l - 1];
        genes[l - 1] = gene_l;
        return this;
    };
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
    // Constructeur par défaut
    Population() : taille_Population(0) {}

    // constructeur de population d'individu*
    Population(vector<Individu *> premiersIndividus)
    {
        individus = premiersIndividus;
        taille_Population = individus.size();
    }

    // surcharge d'opérateur qui permet de concatener deux populations
    Population operator+(const Population &Pop2);

    // Accesseur pour obtenir un individu à un indice donné
    Individu *getIndividu(int index) const
    {
        if (index >= 0 && index < taille_Population)
        {
            return individus[index];
        }
        else
        {
            return nullptr; // Indice invalide
        }
    }

    // Accesseur pour obtenir le nombre d'individus dans la population
    int getTaillePopulation() const
    {
        return taille_Population;
    }
};
;

// permet de créer deux enfants à partir de deux parents + argument de pointeur de la fonction de factory methode cf Factory.hpp
Population hybridation(const Individu &parent_1, const Individu &parent_2, Individu *(*pointeur_FactoryMethod)(IndividuType type));

// prend en argument un population déjà sélectionner et applique la méthode d'hybridation à des couples aléatoires de parents

Population reproduction(const Population parents, Individu *(*pointeur_FactoryMethod)(IndividuType type));

// sélection méthodes
Population selection_roulette(Population &P, double);
#endif

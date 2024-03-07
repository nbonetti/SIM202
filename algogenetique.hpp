#ifndef ALGOGENETIQUE_HPP
#define ALGOGENETIQUE_HPP

#include <fstream>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm> // Pour la fonction std::shuffle
#include <random>    // Pour les générateurs de nombres aléatoire

using namespace std;

// Fonction pour générer un nombre aléatoire entre k et n de manière uniforme
int unif_rand(int k, int n);

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

    virtual Individu *clone() const = 0;
    //=================================================================
    //         fonction propre à la classe Individu
    //=================================================================

    Individu *mutationPermutation();
    Individu *mutationAleatoire();

    IndividuType type;
};

// // création d'un pointeur vers la fonction poids nécessaire pour la sélections
// extern double (Individu::*pointeur_fct_poids)() const;

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
    // constructeur par taille
    Population(int n) : taille_Population(n) {}
    // constructeur de population d'individu*
    Population(vector<Individu *> premiersIndividus)
    {
        individus = premiersIndividus;
        taille_Population = individus.size();
    }

    // getter de tous les individus
    const vector<Individu *> &getIndividus() const
    {
        return individus;
    }

    void addIndividu(Individu *individu)
    {
        individus.push_back(individu);
    }

    void removeIndividu(int index)
    {
        if (index >= 0 && index < taille_Population)
        {
            delete individus[index];
            individus.erase(individus.begin() + index);
            taille_Population--;
        }
        else
        {
            std::cerr << "Erreur : Index d'individu invalide." << std::endl;
        }
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

    void print(ostream &out) const;
};

// fonction qui trie la population selon la fonction d'adaptation
Population trierPopulation(Population &P);

// permet de créer deux enfants à partir de deux parents + argument de pointeur de la fonction de factory methode cf Factory.hpp
Population hybridation(Individu* parent_1, Individu* parent_2, Individu *(*pointeur_FactoryMethod)(IndividuType type), IndividuType type);

// prend en argument un population déjà sélectionner et applique la méthode d'hybridation à des couples aléatoires de parents

Population reproduction(const Population parents, Individu *(*pointeur_FactoryMethod)(IndividuType type), IndividuType type);

#endif
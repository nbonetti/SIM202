#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <random>
using namespace std;

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
protected:
    vector<double> genes;
    int nombreGenes;

public:
    //=================================================================
    //   fonctions virtuelles à définir dans la classe fille
    //=================================================================
    Individu() { type = NoneType; };
    Individu(vector<double> premiersGenes)
    {
        genes = premiersGenes;
        nombreGenes = premiersGenes.size();
        type = NoneType;
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
    Population hybridation(const Individu &partenaire);

    IndividuType type;
};

//=========================================================================================================================
//                                           CLASSE ENFANT AKA CHEMIN
//=========================================================================================================================

class Chemin : public Individu
{

public:
    Chemin() { type = CheminType; };
    Chemin(vector<double> premiersGenes) : Individu(premiersGenes) { type = CheminType; };

    void print(ostream &out) const
    {
        cout << "[";
        for (int i = 0; i < nombreGenes - 1; i++)
        {
            out << genes[i] << ", ";
        }
        out << genes[nombreGenes - 1] << "]" << endl;
    };

    double poids() const
    {
        double poids = 0;
        int nombreGenes; // nb de villes  /// on retourne au point de départ
        for (int i = 0; i < nombreGenes; i++)
        {
            // poids+=; CALCUL A FAIRE
        }
        return poids;
    };

    ~Chemin(){};
};
//=========================================================================================================================
//                                           CREATEUR
//=========================================================================================================================

Individu *FactoryMethod(IndividuType type)
{
    if (type == CheminType)
    {
        return new Chemin();
    }
    else
    {
        return nullptr;
    }
}

//=========================================================================================================================
//                                                CLASSE POPULATION
//=========================================================================================================================

class Population
{
protected:
    vector<Individu *> individus;
    int taille_Population;

public:
    Population(vector<Individu *> premiersIndividus)
    {
        individus = premiersIndividus;
        taille_Population = individus.size();
    }

    Population operator+(const Population &Pop2);
    void print(ostream &out);
};

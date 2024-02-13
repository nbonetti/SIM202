#include "algogenetique.hpp"
#include <iostream>
using namespace std;

int unif_rand(int k, int nombreGenes)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(k, nombreGenes);
    return dis(gen);
};

//=========================================================================================================================
//                         fonctions propres à l'algorithme génétique
//=========================================================================================================================

// flip entre 4 gènes cf projet
Individu *Individu::mutationPermutation()
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
};

// mutation entre deux gènes aléatoires
Individu *Individu::mutationAleatoire()
{
    if (nombreGenes <= 1)
    {
        cout << "mutation impossible car <=2";
        exit(-1);
    }

    int l = unif_rand(0, nombreGenes - 1);
    int k = unif_rand(0, nombreGenes - 1);
    int gene_l = genes[l];
    genes[l] = genes[k];
    genes[k] = gene_l;
};

// création de deux enfants issus de 2 parents
Population Individu::hybridation(const Individu &partenaire)
{
    if (type != partenaire.type)
    {
        exit(-1);
    }
    // Vérifie que les deux parents ont la même taille
    if (nombreGenes != partenaire.nombreGenes)
    {
        cout << "Erreur : Les parents ont des tailles différentes." << std::endl;
        exit(-1);
    }
    // Vérifie que les tableaux de gènes ne sont pas vides
    if (genes.empty() || partenaire.genes.empty())
    {
        cout << "Erreur : Les tableaux de gènes sont vides." << std::endl;
        exit(-1);
    }
    // creer les deux enfants
    Individu *child1 = FactoryMethod(CheminType);
    Individu *child2 = FactoryMethod(CheminType);

    vector<double> genes1, genes2;

    // REMPLIT VECTORS

    child1->setGenes(genes1);
    child2->setGenes(genes2);

    return Population({child1, child2});
};

//=========================================================================================================================
//                                           CLASSE population
//=========================================================================================================================

Population Population ::operator+(const Population &Pop2)
{
    individus.insert(individus.end(), Pop2.individus.begin(), Pop2.individus.end());
    taille_Population = individus.size();
};

//=========================================================================================================================
//                         fonctions virtuelles
//=========================================================================================================================

void Chemin::print(ostream &out) const
{
    cout << "[";
    for (int i = 0; i < nombreGenes - 1; i++)
    {
        out << genes[i] << ", ";
    }
    out << genes[nombreGenes - 1] << "]" << endl;
};

double Chemin::poids() const
{
    double poids = 0;
    int nombreGenes; // nb de villes  /// on retourne au point de départ
    for (int i = 0; i < nombreGenes; i++)
    {
        // poids+=; CALCUL A FAIRE
    }
    return poids;
};
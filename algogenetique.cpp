#include "algogenetique.hpp"
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
Individu *Individu ::mutationPermutation()
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
Individu *Individu ::mutationAleatoire()
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
Individu *Individu ::hybridation(const Individu &partner)
{
    // Vérifie que les deux parents ont la même taille
    if (nombreGenes != partner.nombreGenes)
    {
        cout << "Erreur : Les parents ont des tailles différentes." << std::endl;
        exit(-1);
    }
    // Vérifie que les tableaux de gènes ne sont pas vides
    if (genes.empty() || partner.genes.empty())
    {
        cout << "Erreur : Les tableaux de gènes sont vides." << std::endl;
        exit(-1);
    }
    // creer les deux enfants
};

//=========================================================================================================================
//                                           CLASSE createur
//=========================================================================================================================

Individu *IndividuCreator ::FactoryMethod()
{
    if (type == IndividuType::Chemin)
    {
        cout << "nouveau chemin crée";
        return new Chemin();
    }
    else
    {
        return nullptr;
    }
};

void IndividuCreator ::CreateIndividu(IndividuType)
{
    this->type = type;
    Individu *ptr = this->FactoryMethod();
};

//=========================================================================================================================
//                         fonctions virtuelles
//=========================================================================================================================

void Chemin ::print(ostream &out) const {
    // fonction d'affichage à écrire

};

double Chemin ::poids() const
{
    double poids = 0;
    int nombreGenes; // nb de villes  /// on retourne au point de départ
    for (int i = 0; i < nombreGenes; i++)
    {
        // poids+=; CALCUL A FAIRE
    }
    return poids;
};
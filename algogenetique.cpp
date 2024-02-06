#include "algogenetique.hpp"

//=========================================================================================================================
//                         fonctions propres à l'algorithme génétique
//=========================================================================================================================

// flip entre 4 gènes cf projet
individu *flip()
{
    if (n <= 1)
    {
        cout << "mutation impossible car <=1";
        exit(-1);
    }

    // deux indices alétoirement
    int l = unif_rand(1, n - 1);
    int k = unif_rand(0, n - 2);

    // échange des valeurs
    int gene_k = genes[k];
    genes[k] = genes[k + 1];
    genes[k + 1] = gene_k;

    int gene_l = genes[l];
    genes[k] = genes[l - 1];
    genes[l - 1] = gene_l;
};

// mutation entre deux gènes aléatoires
individu *mutation()
{

    // Choisissez un point de croisement aléatoire
    int pt_rand = unif_rand(0, n - 1);
    // copie des premieres valeurs de genes des enfants
    for (int i = 0; i < pt_rand; ++i)
    {
        cout << "mutation impossible car <=1";
        exit(-1);
    }
    int l = unif_rand(0, n - 1);
    int k = unif_rand(0, n - 1);
    int gene_l = genes[l];
    genes[l] = genes[k];
    genes[k] = gene_l;
};

// création de deux enfants issus de 2 parents
individu *crossover(const individu &partner)
{
    // Vérifie que les deux parents ont la même taille
    if (n != partner.n)
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
}
;

class indiCreator
{
public:
    individu *individuCreator()
    {
        return new individu;
    };
    //=========================================================================================================================
    //                         fonctions virtuelles propres à l'application considérée
    //=========================================================================================================================
    // calcul du poids des gènes
    virtual double poids() = 0;
};

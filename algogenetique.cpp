#include "algogenetique.hpp"
#include <iostream>
#include <algorithm> // Pour la fonction std::shuffle
#include <random>    // Pour les générateurs de nombres aléatoire
using namespace std;

// permet de tirer un nombre aléatoire entre k et n suivant une loi uniforme
int unif_rand(int k, int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(k, n);
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
    return this;
}

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
    return this;
}

double (Individu::*pointeur_fct_poids)() const = &Individu::poids;

//=========================================================================================================================
//                                           CLASSE population
//=========================================================================================================================

// surcharge d'opérateur qui permet de concaténer deux populations

Population Population ::operator+(const Population &Pop2)
{
    individus.insert(individus.end(), Pop2.individus.begin(), Pop2.individus.end());
    taille_Population = individus.size();
    return *this;
};

void Population::print(ostream &out) const
{
    for (const auto &individu : individus)
    {
        individu->print(out); // Utilisation de la fonction print de la classe Individu pour chaque individu dans la population
        out << endl;
    }
}

// création de deux enfants issus de 2 parents
// prend en argument les 2 parents, + un pointeur vers la fonction de factory méthode cf Factory.hpp
Population hybridation(const Individu &parent_1, const Individu &parent_2, Individu *(*pointeur_FactoryMethod)(IndividuType type))

{
    if (parent_1.type != parent_2.type)
    {
        exit(-1);
    }
    // Vérifie que les deux parents ont la même taille
    if (parent_1.nombreGenes != parent_2.nombreGenes)
    {
        cout << "Erreur : Les parents ont des tailles différentes." << std::endl;
        exit(-1);
    }
    // Vérifie que les tableaux de gènes ne sont pas vides
    if (parent_1.genes.empty() || parent_2.genes.empty())
    {
        cout << "Erreur : Les tableaux de gènes sont vides." << std::endl;
        exit(-1);
    }

    // def la taille des individus
    int taille = parent_1.nombreGenes;

    // creer les deux enfants
    Individu *child1 = (*pointeur_FactoryMethod)(IndividuType::CheminType);
    Individu *child2 = (*pointeur_FactoryMethod)(IndividuType::CheminType);

    // Choisissez un point de coupure aléatoire entre 0 et le nombre de gènes
    int point_coupure = rand() % taille;

    // créer les vecteurs de gènes des enfants - leur taille égale à celle des parents avec comme valeur par défaut -1
    vector<double> genes1 = parent_1.genes;
    vector<double> genes2 = parent_2.genes;

    // Copiez les parties restantes des gènes du parent 2 et 1
    for (int i = point_coupure; i < parent_1.nombreGenes; ++i)
    {
        genes1[i] = parent_2.genes[i];
        genes2[i] = parent_1.genes[i];
    }

    child1->setGenes(genes1);
    child2->setGenes(genes2);

    Population enfants = Population({child1, child2});

    return enfants;
};

// prend en argument un population déjà sélectionner et applique la méthode d'hybridation à des couples aléatoires de parents

Population reproduction(const Population parents, Individu *(*pointeur_FactoryMethod)(IndividuType type))
{
    // Crée une copie de la population parentale pour ne pas la modifier
    Population parentsMelanges = parents;

    // Mélange l'ordre des individus dans la population parentale
    std::random_device rd;
    std::mt19937 g(rd());
    vector<Individu *> individus = parentsMelanges.getIndividus();
    std::shuffle(individus.begin(), individus.end(), g);

    Population enfants; // La population des descendants

    // Parcourt les paires de parents mélangés
    for (size_t i = 0; i < parentsMelanges.getTaillePopulation(); i += 2)
    {
        // Assure qu'il reste un parent
        if (i + 1 < parentsMelanges.getTaillePopulation())
        {
            // Obtient les deux parents de manière aléatoire
            const Individu &parent1 = *(parentsMelanges.getIndividu(i));
            const Individu &parent2 = *(parentsMelanges.getIndividu(i + 1));

            // Effectue l'hybridation pour obtenir les enfants
            Population enfants_crees = hybridation(parent1, parent2, pointeur_FactoryMethod);

            // Ajoute les enfants à la population des descendants
            enfants = enfants + enfants_crees;
        }
        else // Si le nombre de parents est impair, ajoute simplement le dernier parent à la population des descendants
        {
            enfants = enfants + Population({parentsMelanges.getIndividu(i)});
        }
    }

    return enfants;
};

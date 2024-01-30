#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <random>
using namespace std;

// fonction qui renvoie un nombre aléatoire entre 1 et n-1 de manière unifrome
int unif_rand(int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, n - 1);
    return dis(gen);
}

class individu
{
private:
    int n;
    vector<int> genes;

public:
    // constructeur avec une taille donnée
    individu(int taille) : n(taille), genes(taille) {}
    // constructeur avec des valeurs données
    individu(const std::vector<int> &geneList) : n(geneList.size()), genes(geneList) {}

    // création de deux enfants avec hybridation avec deux individus
    individu crossover(const individu &partner)
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
        individu enfant_1(n);
        individu enfant_2(n);

        // Choisissez un point de croisement aléatoire
        int pt_rand = unif_rand(n);
        // copie des premieres valeurs de genes des enfants
        for (int i = 0; i < pt_rand; ++i)
        {
            enfant_1.genes[i] = genes[i];
            enfant_2.genes[i] = partner.genes[i];
        }

        // copie des autres valeurs des enfants
        for (int i = pt_rand; i < n; ++i)
        {
            enfant_1.genes[i] = partner.genes[i];
            enfant_2.genes[i] = genes[i];
        }

        return (enfant_1, enfant_2);
    }

    // mutation inverse deux gènes aléatoirement
    individu mutation()
    {
        if (n <= 1)
        {
            cout << "mutation impossible car <=1";
            exit(-1);
        }
        int l = unif_rand(n);
        int k = unif_rand(n);
        int gene_l = genes[l];
        genes[l] = genes[k];
        genes[k] = gene_l;
    };

    class population
    {
    private:
        int m;
        vector<individu> indi;

    public:
        // constructeur avec une taille donnée
        population(int taille) : m(taille), indi(taille) {}
        // constructeur avec des valeurs données
        population(const std::vector<individu> &indiList) : m(indiList.size()), indi(indiList) {}
    };

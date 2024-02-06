#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <random>
using namespace std;

// fonction qui renvoie un nombre aléatoire entre k et n de manière unifrome
int unif_rand(int k, int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(k, n);
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
    // calcul du poids des gènes
    virtual double poids() = 0;

    // flip entre 4 gènes cf projet
    virtual individu *flip() = 0;

    // mutation entre deux gènes aléatoires
    virtual individu *mutation() = 0;

    // création de deux enfants issus de 2 parents
    virtual individu *crossover(const individu &ind) = 0;
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

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
using namespace std;

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

    individu crossover(const individu &partner)
    {
    }

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

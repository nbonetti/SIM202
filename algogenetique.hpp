#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <random>
using namespace std;

// fonction qui renvoie un nombre aléatoire entre k et n de manière uniforme
int unif_rand(int k, int n);

class Individu
{
private:
    vector<double> genes;
    double poid_chemin;
    int n;

public:
    virtual double poids() const = 0;
    Individu *flip();
    Individu *mutation();
    Individu *crossover(const Individu &partner);
};

class Chemin : public Individu
{
private:
    vector<double> genes;
    double poid_chemin;
}
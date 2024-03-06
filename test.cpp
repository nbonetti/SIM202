#include "algogenetique.hpp"
#include "voyage.hpp"
#include "Factory.hpp"
#include "selection.hpp"

using namespace std;

int main()
{
    // Création des données des villes à parcourir
    vector<int> cityNames = {0, 1, 2, 3, 4};
    vector<Point> cityCoords = {Point(0, 0), Point(3, 4), Point(6, 8), Point(10, 5), Point(12, 2)};//coordonnées de chaque ville
    Ville city(cityNames, cityCoords);
    city.calcul_distance();

    // Création de plusieurs chemins initiaux
    vector<vector<double>> paths = {
        {0, 1, 2, 3, 4}, // Chemin 1
        {0, 2, 4, 1, 3}, // Chemin 2
        {0, 3, 2, 1, 4}  // Chemin 3
    };

    // Création des individus pour chaque chemin initial
    vector<Individu *> populationInitiale;
    for (auto &path : paths)
    {
        populationInitiale.push_back(new Chemin(path, city));
    }

    // Création de la population initiale
    Population population(populationInitiale);

    cout << "Population initiale:" << endl;
    population.print(cout);

    // Sélection des individus pour la reproduction
    //Population selection = selection_rang(population);
    //Population selection= select_roulette(population,2);
    Population selection=select_eugenisme(population,2);

    cout << "\nIndividus sélectionnés pour la reproduction:" << endl;
    selection.print(cout);

    /*//Reproduction des individus sélectionnés
    Population enfants = reproduction(selection, FactoryMethod);

    cout << "\nEnfants après reproduction:" << endl;
    enfants.print(cout);*/

    return 0;
}
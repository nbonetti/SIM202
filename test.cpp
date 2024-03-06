#include "algogenetique.hpp"
#include "voyage.hpp"
#include "Factory.hpp"
#include "selection.hpp"

using namespace std;

int main()
{
    //définiton des villes à parcourir et calcul des distances
    vector<int> cityNames = {0,1,2,3,4};
    vector<Point> cityCoords = {Point(0, 0), Point(3, 4), Point(6, 8), Point(10, 5), Point(12, 2)};
    Ville city(cityNames, cityCoords);
    city.calcul_distance();

    cout << "Distances between cities:" << endl;
    for (const auto &row : city.distances)
    {
        for (double dist : row)
        {
            cout << dist << "\t";
        }
        cout << endl;
    }
    // Génération de plusieurs chemins initiaux
    vector<vector<double>>initialPaths = {
        {0, 1, 2, 3, 4},  // Chemin 1
        {0, 2, 1, 3, 4},  // Chemin 2
        {0, 4, 3, 2, 1}   // Chemin 3
    };
    //cre le chemin initial à partir de la liste des chemins
    vector<double> intGenes;
    intGenes.reserve(initialPaths[0].size());
    for (double gene : initialPaths[0])
    {
        intGenes.push_back(static_cast<int>(gene));
    }   
    Chemin path(intGenes, city);

    cout << "Initial path: ";
    path.print(cout);
    cout << "Initial path weight: " << path.poids() << endl;

    // on a un chemin et on a calculé la distance de parcours
    // maintenant on va essayer d'appliquer mutation à l'indivu soit au chemin formé
    //  Mutation du chemin
    path.mutationPermutation(); // Vous pouvez choisir entre mutationPermutation() et mutationAleatoire() selon votre besoin
    //  Affichage du chemin après mutation et recalcul de la distance parcourue
    cout << "Path after mutation: ";
    path.print(cout);
    cout << "Path weight after mutation: " << path.poids() << endl;

    //-------------------------test de sélection ---------------------------------------//

    // Création d'une population de chemins
    vector<Individu *> populationInitiale;
    //populationInitiale.push_back(&path); // Ajout du chemin initial à la population
    for (const auto &genes : initialPaths)
    {
        populationInitiale.push_back(new Chemin(genes, city));
    }
    Population population(populationInitiale);

    cout << "la pop est \n";
    population.print(cout);
    cout<<endl;
    // Test de la fonction de sélection
    //Population selection = selection_eugenisme(population, 1);
    Population selection = selection_rang(population);
    // Affichage des individus sélectionnés
    cout << "Individus sélectionnés: " << endl;
    selection.print(cout);
    cout<<endl;
    // for (int i = 0; i < selection.getTaillePopulation(); ++i)
    // {
    //     Chemin *individu = dynamic_cast<Chemin *>(selection.getIndividu(i));
    //     if (individu)
    //     {
    //         cout << "Individu " << i + 1 << ": ";
    //         individu->print(cout);
    //         cout << "Poids de l'individu " << i + 1 << ": " << individu->poids() << endl;
    //     }
    // }

    //-------------------------test de reproduction---------------------------------------//

    // Test de la fonction de reproduction
    Population enfants = reproduction(selection, FactoryMethod);

    cout << "affiche les enfants \n";
    enfants.print(cout);
    cout<<endl;

    return (0);
}

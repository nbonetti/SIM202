#include "algogenetique.hpp"
#include "voyage.hpp"
#include "Factory.hpp"
#include "selection.hpp"

using namespace std;

int main()
{
    vector<string> cityNames = {"A", "B", "C", "D", "E"};
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
    vector<double> initialGenes = {0, 1, 2, 3, 4}; // Initial path: A -> B -> C->D->E
    Chemin path(initialGenes, city);

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
    populationInitiale.push_back(&path); // Ajout du chemin initial à la population

    Population population(populationInitiale);

    // Test de la fonction de sélection
    Population selection = select_roulette(population, path.nombreGenes);

    // Affichage des individus sélectionnés
    cout << "Individus sélectionnés: " << endl;
    for (int i = 0; i < selection.getTaillePopulation(); ++i)
    {
        Chemin *individu = dynamic_cast<Chemin *>(selection.getIndividu(i));
        if (individu)
        {
            cout << "Individu " << i + 1 << ": ";
            individu->print(cout);
            cout << "Poids de l'individu " << i + 1 << ": " << individu->poids() << endl;
        }
    }

    //-------------------------test de reproduction---------------------------------------//

    // Test de la fonction de reproduction
    Population enfants = reproduction(selection, FactoryMethod);

    // Affichage des enfants générés
    cout << "Enfants générés: " << endl;
    for (int i = 0; i < enfants.getTaillePopulation(); ++i)
    {
        Chemin *enfant = dynamic_cast<Chemin *>(enfants.getIndividu(i));
        if (enfant)
        {
            cout << "Enfant " << i + 1 << ": ";
            enfant->print(cout);
            cout << "Poids de l'enfant " << i + 1 << ": " << enfant->poids() << endl;
        }
    }

    return (0);
}

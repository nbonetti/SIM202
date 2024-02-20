#include "algogenetique.hpp"
#include "voyage.hpp"
#include "Factory.hpp"

using namespace std;

int main()
{
    vector<string> cityNames = {"A", "B", "C"};
    vector<Point> cityCoords = {Point(0, 0), Point(3, 4), Point(6, 8)};
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
    vector<double> initialGenes = {0, 1, 2}; // Initial path: A -> B -> C
    Chemin path(initialGenes, city);

    cout << "Initial path: ";
    path.print(cout);

    cout << "Initial path weight: " << path.poids() << endl;


    //on a un chemin et on a calculé la distance de parcours 
    //maintenant on va essayer d'appliquer mutation à l'indivu soit au chemin formé 
    // Mutation du chemin
    path.mutationPermutation(); // Vous pouvez choisir entre mutationPermutation() et mutationAleatoire() selon votre besoin
    // Affichage du chemin après mutation et recalcul de la distance parcourue
    cout << "Path after mutation: ";
    path.print(cout);
    cout << "Path weight after mutation: " << path.poids() << endl;

    return (0);
}


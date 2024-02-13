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
    return (0);
}

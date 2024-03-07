#include <cmath>
#include <cstdlib>
#include <vector>
#include <random>
#include <ctime>
#include <list>
#include <iostream>
#include <fstream>
#include <string>

#include "algogenetique.hpp"
#include "voyage.hpp"
#include "Factory.hpp"
#include "selection.hpp"
#include "csv.hpp"
using namespace std;

#include <cmath>
#include <cstdlib>
#include <vector>
#include <random>
#include <ctime>
#include <list>
#include <iostream>
#include <fstream>
#include <string>

#include "algogenetique.hpp"
#include "voyage.hpp"
#include "Factory.hpp"
#include "selection.hpp"
using namespace std;

Population algogenetique(Population &Pop_initiale, int nb_iter, int nb_reproducteurs)
{

    //====================================================================================================================================
    //                          initialisation
    //====================================================================================================================================

    int k = 0;
    // nb de parents nécessaires pour que la population après reproduction et sélection garde la même taille intiale
    int nb_parents_conservés = Pop_initiale.getTaillePopulation() - nb_reproducteurs;

    Population population_parents = Pop_initiale;
    Population parents_selectionnés;
    Population enfants;
    Population parents_conservés;

    //====================================================================================================================================
    //                          iteration jusqu'à fin (critère d'arret )
    //====================================================================================================================================
    while (k < nb_iter)
    {
        //====================================================================================================================================
        //                          SELECTION DES REPRODUCTEURS
        //====================================================================================================================================

        // proba de gagner lors de la selection par tournoi
        double proba_tournoi;

        // parents_selectionnés = selection_eugenisme(population_parents, nb_reproducteurs);
        // parents_selectionnés = selection_roulette(population_parents, nb_reproducteurs);
        parents_selectionnés = selection_rang(population_parents, nb_reproducteurs);
        // parents_selectionnés = selection_tournoi(population_parents, nb_reproducteurs, proba_tournoi);

        //====================================================================================================================================
        //                          REPRODUCTION DES ENFANTS + MUTATION
        //====================================================================================================================================
        // il faut choisir la mutation appliquée aux enfants
        // enfants des parents issus de la sélection
        enfants = reproduction(parents_selectionnés, FactoryMethod);

        // mutation des enfants
        for (int i = 0; i < nb_reproducteurs; i++)
        {
            enfants.getIndividu(i)->mutationAleatoire();
            // enfants.getIndividu(i)->mutationPermutation();
        }

        //====================================================================================================================================
        //                          COMPLEMENT DE LA POPULATION ENFANTS POUR CONSERVER LE NB D'INDIVIDUS
        //====================================================================================================================================

        // à définir si sélection par tournoi
        double proba_tournoi_conservés;
        // sélection des parents que l'on va conservés pour la prochaine génération
        // parents_conservés = selection_eugenisme(population_parents, nb_reproducteurs);
        // parents_selectionnés = selection_roulette(population_parents, nb_parents_conservés);
        parents_conservés = selection_rang(population_parents, nb_parents_conservés);
        // parents_conservés = selection_tournoi(population_parents, nb_parents_conservés, proba_tournoi_conservés);

        enfants = enfants + parents_conservés;

        //====================================================================================================================================
        //                         ITERATEURS
        //====================================================================================================================================

        population_parents = enfants;
        k = k + 1;
    };

    // la population finale est
    Population pop_finale = population_parents;

    return pop_finale;
};

int main()

{

    //=========================================================================================================
    //                                             LECTURE DU FICHIER
    //==========================================================================================================

    vector<vector<double>> content = csv_reader("Villes_csv"); // on récupère le fichier

    //========================================================================================
    //                                      DEBUT
    //========================================================================================

    vector<int> citynumber; // index des villes dans le fichier
    vector<Point> coord;    // coordonées (x,y)

    for (const auto &row : content)
    {
        cout << row[0];
        citynumber.push_back(row[0]);           // Première colonne : indices
        coord.push_back(Point(row[1], row[2])); // Deuxième et troisième colonnes : coordonnées x et y
    }
    // création de l'objet ville
    Ville city(citynumber, coord);
    city.calcul_distance();
    city.print(cout);
    cout << "Distances between cities:" << endl;
    for (const auto &row : city.distances)
    {
        for (double dist : row)
        {
            cout << dist << "\t";
        }
        cout << endl;
    }

    /*vector<double> vmin;







//==============================================================================
//                                  DEBUT
//==============================================================================
    Population paths;//population initaile avec tou sles chemins possibles avec le fichier de départ
    int nombre_chemins; //choisir le nombre de chemins que l'on veut dans notre porpulation
    int i = 0;
    int k = 0;
//faire une fonction qui génère la population totale avec tous les chemins possibles avec le fichier de départ
    generateur_chemins(nombre_chemins,city,paths);
    paths.print(cout);


    Population enfants;
    int p; //choisir nous mêmes
    //test d'arrêt
    while (k<=5 && i<=100)
    {
        //SELECTION DE LA POPULATION
        Population selection=selection_rang(paths);
        //Population selection=select_roulette(paths,p);
        //Population selection=select_eugenisme(paths,p);
        cout << "\nIndividus sélectionnés pour la reproduction:" << endl;
        selection.print(cout);


        paths.trierPopulation(&Individu::poids);
        Individu* I=paths.getIndividu(0);
        double minimum= I->poids();

        //HYBRIDATION -REPRODUCTION
        // Reproduction des individus sélectionnés
        enfants = reproduction(selection, FactoryMethod);
        cout << "\nEnfants après reproduction:" << endl;
        enfants.print(cout);


        //MUTATION
        for (int i = 0; i < enfants.getTaillePopulation(); ++i)
        {
            enfants.getIndividu(i)->mutationPermutation();
        }

        cout << "\nEnfants après mutation:" << endl;
        enfants.print(cout);






    }*/

    return 0;
}
